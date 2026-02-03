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
    wait(500);
    intermissionTimer.wait(intermissionDelay);
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
    case Actions::GameOver:
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
    for (uint16_t i = playerClearance; i < playerClearance + player.width; ++i)
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
        double attenuation = std::clamp(1.0 - 0.085 * static_cast<double>(distance), 0.0, 1.0);

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
      bool hasEnteredRegion = start <= playerClearance + player.width;
      bool hasNotExitedRegion = end >= playerClearance;

      if (isUnmatchingColor && hasEnteredRegion && hasNotExitedRegion)
      {
        state.current = Actions::GameOver;
      }
    }
  }

  void Controller::orchestrateCollection()
  {
    if (isReady())
    {
      if (intermissionTimer.isReady())
      {
        state.current = Actions::WindDown;
      }

      if (state.current == Actions::ActiveGame)
      {

        flareManager.dispatch(speed);
        uint32_t timeDelay = (esp_random() % interval) + gap;
        wait(timeDelay);
      }

      bool shouldStartNextRound = state.current == Actions::WindDown && flareManager.size() == 1;
      if (shouldStartNextRound)
      {
        intermissionTimer.wait(intermissionDelay);
        state.current = Actions::ActiveGame;
      }
    }
  }

  void Controller::gameOver()
  {
    if (contextManager->controller.wasPressed(::Player::ControllerButton::Start))
    {
      state.current = Actions::Startup;
      state.reset();
      contextManager->stateManager.displayShouldUpdate = true;
      flareManager.reset();
      intermissionTimer.wait(intermissionDelay);
      return;
    }

    for (uint16_t i = 0; i < contextManager->config.numLeds; ++i)
    {
      contextManager->leds.buffer[i] = Lights::ColorCode::GameRed;
    }
  }
}