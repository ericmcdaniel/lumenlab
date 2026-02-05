#include "games/phase-evasion/driver.h"
#include "player/controller.h"
#include "logger.h"

namespace Games::PhaseEvasion
{
  Driver::Driver(SystemCore::ContextManager *ctx) : contextManager{ctx},
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

  void Driver::nextEvent()
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
      // checkCollision();
      renderFlare();
      renderPlayer();
      renderGem();
      break;
    case Actions::MuzzleFlash:
      muzzleFlash();
      break;
    case Actions::GameOver:
      gameOver();
      renderFlare();
      renderPlayer();
      break;
    }
  }

  void Driver::getUpdates()
  {
    player.checkColorChangeRequest();
    flareManager.updatePositions();
    auto leftInput = contextManager->controller.leftAnalog();
    player.move(leftInput.x, 1.5, false);
  }

  void Driver::renderPlayer()
  {
    for (uint16_t i = 0; i < player.width; ++i)
    {
      uint16_t index = (player.getPosition() + i) % SystemCore::Configuration::numLeds;
      contextManager->leds.buffer[index] = player.getColor();
    }
  }

  void Driver::renderFlare()
  {
    for (const auto &flare : flareManager)
    {
      if (!flare.isActive())
        continue;

      uint16_t flareHead = std::max(flare.getPosition() - flare.width, 0);
      uint16_t flareTail = std::min(flare.getPosition(), SystemCore::Configuration::numLeds);

      for (uint16_t i = flareHead; i < flareTail; ++i)
      {
        uint16_t distance = i - flareHead;
        double attenuation = std::clamp(1.0 - 0.08 * static_cast<double>(distance), 0.0, 1.0);

        contextManager->leds.buffer[i] = flare.getColor() * attenuation;
      }
    }
  }

  void Driver::renderGem()
  {
  }

  void Driver::checkCollision()
  {
    for (const auto &flare : flareManager)
    {
      if (!flare.isActive())
        continue;

      uint16_t flareStart = std::max(flare.getPosition() - flare.width, 0);
      uint16_t flareEnd = std::min(flare.getPosition(), SystemCore::Configuration::numLeds);

      bool isUnmatchingColor = player.getColor() != flare.getColor();
      bool hasEnteredRegion = flareStart <= player.getPosition() + player.width;
      bool hasNotExitedRegion = flareEnd >= player.getPosition();

      if (isUnmatchingColor && hasEnteredRegion && hasNotExitedRegion)
      {
        state.current = Actions::MuzzleFlash;
        wait(20);
      }
    }
  }

  void Driver::orchestrateCollection()
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

  void Driver::muzzleFlash()
  {
    for (uint16_t i = 0; i < SystemCore::Configuration::numLeds; ++i)
    {
      contextManager->leds.buffer[i] = Lights::Color::White;
    }

    if (isReady())
    {
      state.current = Actions::GameOver;
    }
  }

  void Driver::gameOver()
  {
    static float gameOverPhaseShift = static_cast<float>(player.getPosition());

    for (uint16_t i = 0; i <= SystemCore::Configuration::numLeds; ++i)
    {
      float offset = std::cos((2.0f * M_PI * i / SystemCore::Configuration::numLeds) + (2.0f * M_PI * gameOverPhaseShift / SystemCore::Configuration::numLeds));
      float phase = offset * 127 + 128;
      contextManager->leds.buffer[i] = {static_cast<uint8_t>(std::floor(phase)),
                                        static_cast<uint8_t>(0),
                                        static_cast<uint8_t>(0)};
    }

    gameOverPhaseShift += 0.5f;
    if (gameOverPhaseShift > SystemCore::Configuration::numLeds)
      gameOverPhaseShift = 0.0;

    if (contextManager->controller.wasPressed(::Player::ControllerButton::Start))
    {
      state.current = Actions::Startup;
      state.reset();
      contextManager->stateManager.displayShouldUpdate = true;
      gameOverPhaseShift = static_cast<float>(player.getPosition());
      flareManager.reset();
      windDownTimer.wait(windDownLength);
    }
  }

  void Driver::reset()
  {
    interval = 2000;
    gap = 1500;
    speed = 0.4f;
    wait(500);
  }
}