#include "games/phase-evasion/phase-evasion-core.h"

namespace Games
{
  PhaseEvasionCore::PhaseEvasionCore(Core::ContextManager *ctx) : contextManager{ctx}, player{PhaseEvasionPlayer{contextManager}}
  {
    contextManager->stateManager.getPhaseEvasionGameState().reset();
  }

  void PhaseEvasionCore::nextEvent()
  {
  }
}