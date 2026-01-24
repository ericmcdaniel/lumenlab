#include "games/phase-evasion/flare-manager.h"
#include "logger.h"

namespace Games::PhaseEvasion
{
  FlareManager::FlareManager()
  {
    dispatch();
  }

  void FlareManager::dispatch()
  {
    auto flare = flarePool.begin();
    while (flare != flarePool.end())
    {
      if (!flare->isActive())
      {
        flare->activate();
        logf("Flare #%lu dispatched", (unsigned long)size());
        return;
      }
      ++flare;
    }
    logf("Flare dispatch: no free flares");
  }

  void FlareManager::updatePositions()
  {
    for (auto flare = flarePool.begin(); flare != flarePool.end(); ++flare)
    {
      if (!flare->isActive())
        continue;

      flare->updatePosition();
    }
  }

  const size_t FlareManager::size() const
  {
    return std::count_if(flarePool.begin(), flarePool.end(), [](const Flare &flare)
                         { return flare.isActive(); });
  }
}