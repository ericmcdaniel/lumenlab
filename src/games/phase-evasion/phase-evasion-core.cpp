#include "games/phase-evasion/phase-evasion-core.h"
#include "logger.h"

namespace Games
{
  PhaseEvasionCore::PhaseEvasionCore(Core::ContextManager *ctx) : contextManager{ctx}, player{PhaseEvasionPlayer{contextManager}}
  {
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
      player.checkColorChangeRequest();
      renderUserColor();
      break;
    }
  }

  void PhaseEvasionCore::renderUserColor()
  {
    for (uint16_t i = 1; i < 8; ++i)
    {
      contextManager->leds.buffer[i] = player.getColor();
    }
  }
}