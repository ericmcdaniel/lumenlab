#include "games/phase-evasion/phase-evasion-flare-manager.h"

namespace Games
{
  PhaseEvasionFlareManager::PhaseEvasionFlareManager(Core::ContextManager *ctx) : contextManager{ctx}
  {
    flares.reserve(10);
    flares.push_back(ctx);
  }
}