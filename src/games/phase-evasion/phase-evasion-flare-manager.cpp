#include "games/phase-evasion/phase-evasion-flare-manager.h"
#include "logger.h"

namespace Games
{
  PhaseEvasionFlareManager::PhaseEvasionFlareManager()
  {
    flares.emplace_back(0.75f);
  }

  void PhaseEvasionFlareManager::dispatch()
  {
    flares.emplace_back(0.75f);
  }

  void PhaseEvasionFlareManager::updatePositions()
  {
    bool started = false;
    fl::vector<PhaseEvasionFlare> survivors;

    for (auto itr = flares.begin(); itr != flares.end(); ++itr)
    {
      itr->updatePosition();

      if (itr->getPosition() > 0)
      {
        if (started)
        {
          survivors.push_back(fl::move(*itr));
        }
      }
      else
      {
        if (!started)
        {
          started = true;
          survivors.reserve(flares.size());
          for (auto prev = flares.begin(); prev != itr; ++prev)
          {
            survivors.push_back(fl::move(*prev));
          }
        }
      }
    }

    if (started)
    {
      flares.swap(survivors);
    }
  }
}