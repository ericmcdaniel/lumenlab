#include "games/phase-evasion/phase-evasion-flare-manager.h"

namespace Games
{
  PhaseEvasionFlareManager::PhaseEvasionFlareManager(Core::ContextManager *ctx) : contextManager{ctx}
  {
    flares.emplace_back(0.75f);
  }

  void PhaseEvasionFlareManager::updatePositions()
  {
    fl::vector<PhaseEvasionFlare> survivors;
    for (auto itr = flares.begin(); itr != flares.end(); ++itr)
    {
      itr->updatePosition();
      if (itr->getPosition() > 0)
      {
        survivors.push_back(fl::move(*itr));
      }
    }
    flares.swap(survivors);
  }
}