#include "games/phase-evasion/controller.h"
#include "player/controller.h"
#include "logger.h"

namespace Games::PhaseEvasion
{
  Controller::Controller(SystemCore::ContextManager *ctx) : contextManager{ctx},
                                                            player{ctx, playerWidth},
                                                            flareManager{ctx}
  {
    state = contextManager->stateManager.getPhaseEvasionGameState();
    state.reset();
    state.current = Actions::Startup;
    reset();
    wait(500);
    windDownTimer.wait(windDownLength);
  }

  void Controller::nextEvent()
  {
    switch (state.current)
    {
    case Actions::Startup:
      if (isReady())
      {
        state.current = Actions::ActiveGame;
        log("Starting new game.");
      }
      break;
    case Actions::ActiveGame:
    case Actions::WindDown:
      getUpdates();
      orchestrateCollection();
      checkCollision();
      renderFlare();
      renderPlayer();
      break;
    case Actions::MuzzleFlash:
      muzzleFlash();
      break;
    case Actions::GameOver:
      renderFlare();
      renderPlayer();
      gameOver();
      break;
    }
  }

  void Controller::getUpdates()
  {
    player.checkColorChangeRequest();
    flareManager.updatePositions();
  }

  void Controller::renderPlayer()
  {
    for (uint16_t i = playerOffset; i < playerOffset + player.width; ++i)
    {
      contextManager->leds.buffer[i] = player.getColor();
    }
  }

  void Controller::renderFlare()
  {
    for (const auto &flare : flareManager)
    {
      if (!flare.isActive())
        continue;

      uint16_t flareHead = std::max(flare.getPosition() - flare.width, 0);
      uint16_t flareTail = std::min(flare.getPosition(), contextManager->config.numLeds);

      for (uint16_t i = flareHead; i < flareTail; ++i)
      {
        uint16_t distance = i - flareHead;
        double attenuation = std::clamp(1.0 - 0.08 * static_cast<double>(distance), 0.0, 1.0);

        contextManager->leds.buffer[i] = flare.getColor() * attenuation;
      }
    }
  }

  void Controller::checkCollision()
  {
    for (const auto &flare : flareManager)
    {
      if (!flare.isActive())
        continue;

      uint16_t start = std::max(flare.getPosition() - flare.width, 0);
      uint16_t end = std::min(flare.getPosition(), contextManager->config.numLeds);
      bool isUnmatchingColor = player.getColor() != flare.getColor();
      bool hasEnteredRegion = start <= playerOffset + player.width;
      bool hasNotExitedRegion = end >= playerOffset;

      if (isUnmatchingColor && hasEnteredRegion && hasNotExitedRegion)
      {
        state.current = Actions::MuzzleFlash;
        wait(20);
      }
    }
  }

  void Controller::orchestrateCollection()
  {
    if (isReady())
    {
      if (windDownTimer.isReady())
      {
        state.current = Actions::WindDown;
      }

      if (state.current == Actions::ActiveGame)
      {
        flareManager.dispatch(speed);
        uint32_t timeDelay = static_cast<uint32_t>((esp_random() % static_cast<uint32_t>(interval)) + gap);
        wait(timeDelay);
      }

      bool shouldStartNextRound = state.current == Actions::WindDown && flareManager.size() == 2;
      if (shouldStartNextRound)
      {
        windDownTimer.wait(windDownLength);
        state.current = Actions::ActiveGame;
        speed *= 1.07;
        interval *= 0.85;
        gap *= 0.85;
      }
    }
  }

  void Controller::muzzleFlash()
  {
    for (uint16_t i = 0; i < contextManager->config.numLeds; ++i)
    {
      contextManager->leds.buffer[i] = Lights::Color::White;
    }

    if (isReady())
    {
      state.current = Actions::GameOver;
    }
  }

  void Controller::gameOver()
  {
    static float gameOverPhaseShift = static_cast<float>(contextManager->leds.size() / 3.0);

    for (uint16_t i = playerOffset * 2 + player.width; i <= contextManager->leds.size(); ++i)
    {
      float offset = std::cos((2.0f * M_PI * i / contextManager->leds.size()) + (2.0f * M_PI * gameOverPhaseShift / contextManager->leds.size()));
      float phase = offset * 127 + 128;
      contextManager->leds.buffer[i] = {static_cast<uint8_t>(std::floor(phase)),
                                        static_cast<uint8_t>(0),
                                        static_cast<uint8_t>(0)};
    }

    gameOverPhaseShift += 0.5f;
    if (gameOverPhaseShift > contextManager->leds.size())
      gameOverPhaseShift = 0.0;

    if (contextManager->controller.wasPressed(::Player::ControllerButton::Start))
    {
      state.current = Actions::Startup;
      state.reset();
      contextManager->stateManager.displayShouldUpdate = true;
      gameOverPhaseShift = static_cast<float>(contextManager->leds.size() / 3.0);
      flareManager.reset();
      windDownTimer.wait(windDownLength);
    }
  }

  void Controller::reset()
  {
    interval = 2000;
    gap = 1500;
    speed = 0.4f;
  }
}