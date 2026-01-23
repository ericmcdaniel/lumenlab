#include "games/phase-evasion/flare-manager.h"
#include "logger.h"

namespace Games::PhaseEvasion
{
  FlareManager::FlareManager()
  {
    flares.emplace_back(0.75f);
  }

  void FlareManager::dispatch()
  {
    flares.emplace_back(0.75f);
  }

  void FlareManager::updatePositions()
  {
    bool started = false;
    fl::vector<Flare> survivors;

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