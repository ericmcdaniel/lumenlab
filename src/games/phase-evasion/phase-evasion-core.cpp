#include "games/phase-evasion/phase-evasion-core.h"

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
      }
      break;
    case PhaseEvasionStates::ActiveGame:
      break;
    }
  }
}