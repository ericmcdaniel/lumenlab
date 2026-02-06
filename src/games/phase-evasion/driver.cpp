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
    gem.wait(gemRespawnDelay);
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
      assessDifficulty();
      checkCollision();
      checkGemCapture();
      renderFlare();
      renderGem();
      renderPlayer();
      break;
    case Actions::MuzzleFlash:
      muzzleFlash();
      break;
    case Actions::GameOver:
      gameOver();
      renderFlare();
      renderGem();
      renderPlayer();
      break;
    }
  }

  void Driver::getUpdates()
  {
    player.checkColorChangeRequest();
    flareManager.updatePositions();
    auto leftAnalog = contextManager->controller.leftAnalog();
    player.move(leftAnalog.x, 1.25, false);
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

      if (state.current == Actions::GameOver)
      {
        if (!flare.impacted)
          continue;
      }

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
    if (!gem.isActive() || !gem.isReady())
      return;

    uint16_t gemLeft = std::max(gem.getPosition() - gem.width, 0);
    uint16_t gemRight = std::min(gem.getPosition(), SystemCore::Configuration::numLeds);

    for (uint16_t i = gemLeft; i < gemRight; ++i)
    {
      contextManager->leds.buffer[i] = gem.getColor();
    }
  }

  void Driver::checkCollision()
  {
    for (auto &flare : flareManager)
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
        flare.impacted = true;
        state.current = Actions::MuzzleFlash;
        gameOverPhaseShift = static_cast<float>(((SystemCore::Configuration::numLeds / 2) + player.getPosition()) % SystemCore::Configuration::numLeds);
        wait(20);
      }
    }
  }

  void Driver::checkGemCapture()
  {
    if (!gem.isActive() && gem.isReady())
    {
      const auto randGemPosition = static_cast<uint16_t>((esp_random() % static_cast<uint32_t>(SystemCore::Configuration::numLeds)) + gem.width);
      gem.spawn(randGemPosition);
      gemTimeoutTimer.wait(gemCaptureDelay);
    }

    if (gem.isActive() && gem.isReady())
    {
      if (!gemTimeoutTimer.isReady())
      {
        uint16_t gemStart = std::max(gem.getPosition() - gem.width, 0);
        uint16_t gemEnd = std::min(gem.getPosition(), SystemCore::Configuration::numLeds);

        bool hasEnteredRegion = gemStart <= player.getPosition() + player.width;
        bool hasNotExitedRegion = gemEnd >= player.getPosition();

        if (hasEnteredRegion && hasNotExitedRegion) // player captured the gem
        {
          gem.capture();
          contextManager->stateManager.getPhaseEvasionGameState().gemsCaptured++;
          contextManager->stateManager.displayShouldUpdate = true;
          gem.wait(gemRespawnDelay);
        }
      }
      else // gem timed out, player took too long
      {
        gem.capture();
        gem.wait(gemRespawnDelay);
      }
    }
  }

  void Driver::assessDifficulty()
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
        interval *= 0.8;
        gap *= 0.82;
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

    for (uint16_t i = 0; i <= SystemCore::Configuration::numLeds; ++i)
    {
      float offset = std::cos((2.0f * M_PI * i / SystemCore::Configuration::numLeds) - (2.0f * M_PI * static_cast<uint16_t>(gameOverPhaseShift) / SystemCore::Configuration::numLeds));
      float phase = offset * 127.5 + 127.5;
      contextManager->leds.buffer[i] = {static_cast<uint8_t>(std::floor(phase) * 0.95),
                                        static_cast<uint8_t>(std::floor(phase) * 0.15),
                                        static_cast<uint8_t>(std::floor(phase) * 0.25)};
    }

    gameOverPhaseShift += std::cos(gameOverPhaseOffset) / 16.0f;
    gameOverPhaseOffset += 1.0 / 32.0f;

    if (gameOverPhaseShift > SystemCore::Configuration::numLeds)
      gameOverPhaseShift = 0.0;

    if (contextManager->controller.wasPressed(::Player::ControllerButton::Start))
    {
      state.current = Actions::Startup;
      state.reset();
      contextManager->stateManager.displayShouldUpdate = true;
      reset();
      windDownTimer.wait(windDownLength);
    }
  }

  void Driver::reset()
  {
    interval = 2500;
    gap = 1600;
    speed = 0.4f;
    gem.capture();
    gem.wait(gemRespawnDelay);
    flareManager.reset();
    player.setPosition(static_cast<uint16_t>(0));
    wait(500);
  }
}