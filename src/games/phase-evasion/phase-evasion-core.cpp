#include "games/phase-evasion/phase-evasion-core.h"
#include "logger.h"

namespace Games
{
  PhaseEvasionCore::PhaseEvasionCore(Core::ContextManager *ctx) : contextManager{ctx},
                                                                  player{ctx}
  {
    flareMgr.flares.push_back(ctx);
    state = contextManager->stateManager.getPhaseEvasionGameState();
    state.reset();
    state.current = PhaseEvasionStates::Startup;
    wait(500);
  }

  void PhaseEvasionCore::nextEvent()
  {
    switch (state.current)
    {
    case PhaseEvasionStates::Startup:
      if (isReady())
      {
        state.current = PhaseEvasionStates::ActiveGame;
        log("Starting new game.");
      }
      break;
    case PhaseEvasionStates::ActiveGame:
      getUpdates();
      checkCollision();
      renderFlare();
      renderUserColor();
      break;
    case PhaseEvasionStates::GameOver:
      for (uint16_t i = 0; i < contextManager->config.numLeds; ++i)
      {
        contextManager->leds.buffer[i] = Lights::ColorCode::GameRed;
      }
      break;
    }
  }

  void PhaseEvasionCore::getUpdates()
  {
    player.checkColorChangeRequest();
    flareMgr[0].updatePosition();
  }

  void PhaseEvasionCore::renderUserColor()
  {
    for (uint16_t i = playerClearance; i < playerClearance + player.width; ++i)
    {
      contextManager->leds.buffer[i] = player.getColor();
    }
  }

  void PhaseEvasionCore::renderFlare()
  {
    uint16_t start = std::max(flareMgr[0].getPosition() - flareMgr[0].width, 0);
    uint16_t end = std::min(flareMgr[0].getPosition(), contextManager->config.numLeds);

    for (uint16_t i = start; i < end; ++i)
    {
      contextManager->leds.buffer[i] = flareMgr[0].getColor();
    }
  }

  void PhaseEvasionCore::checkCollision()
  {
    uint16_t start = std::max(flareMgr[0].getPosition() - flareMgr[0].width, 0);
    uint16_t end = std::min(flareMgr[0].getPosition(), contextManager->config.numLeds);

    if (start <= playerClearance + player.width && end >= playerClearance && player.getColor() != flareMgr[0].getColor())
    {
      state.current = PhaseEvasionStates::GameOver;
    }
  }
}