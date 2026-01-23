#include "games/phase-evasion/phase-evasion-core.h"
#include "logger.h"

namespace Games::PhaseEvasion
{
  Core::Core(::Core::ContextManager *ctx) : contextManager{ctx},
                                            player{ctx}
  {
    state = contextManager->stateManager.getPhaseEvasionGameState();
    state.reset();
    state.current = Actions::Startup;
    wait(500);
  }

  void Core::nextEvent()
  {
    switch (state.current)
    {
    case Actions::Startup:
      if (isReady())
      {
        state.current = Actions::ActiveGame;
        wait(1000);
        log("Starting new game.");
      }
      break;
    case Actions::ActiveGame:
      getUpdates();
      checkGrowth();
      checkCollision();
      renderFlare();
      renderUserColor();
      break;
    case Actions::GameOver:
      for (uint16_t i = 0; i < contextManager->config.numLeds; ++i)
      {
        contextManager->leds.buffer[i] = Lights::ColorCode::GameRed;
      }
      break;
    }
  }

  void Core::getUpdates()
  {
    player.checkColorChangeRequest();
    flareMgr.updatePositions();
  }

  void Core::renderUserColor()
  {
    for (uint16_t i = playerClearance; i < playerClearance + player.width; ++i)
    {
      contextManager->leds.buffer[i] = player.getColor();
    }
  }

  void Core::renderFlare()
  {
    for (const auto &flare : flareMgr)
    {
      uint16_t start = std::max(flare.getPosition() - flare.width, 0);
      uint16_t end = std::min(flare.getPosition(), contextManager->config.numLeds);

      for (uint16_t i = start; i < end; ++i)
      {
        contextManager->leds.buffer[i] = flare.getColor();
      }
    }
  }

  void Core::checkCollision()
  {
    for (const auto &flare : flareMgr)
    {
      uint16_t start = std::max(flare.getPosition() - flare.width, 0);
      uint16_t end = std::min(flare.getPosition(), contextManager->config.numLeds);

      if (start <= playerClearance + player.width && end >= playerClearance && player.getColor() != flare.getColor())
      {
        state.current = Actions::GameOver;
      }
    }
  }

  void Core::checkGrowth()
  {
    if (isReady())
    {
      flareMgr.dispatch();
      wait(1000);
    }
  }
}