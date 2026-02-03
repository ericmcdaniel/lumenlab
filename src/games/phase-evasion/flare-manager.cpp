#include "games/phase-evasion/flare-manager.h"
#include "common.h"
#include "logger.h"

namespace Games::PhaseEvasion
{
  void FlareManager::dispatch(float speed)
  {
    auto flare = flarePool.begin();
    while (flare != flarePool.end())
    {
      if (!flare->isActive())
      {
        uint16_t colorIndex = static_cast<uint16_t>(esp_random()) % arraySize(Lights::colorPalette);
        flare->activate(Lights::colorPalette[colorIndex], speed);
        return;
      }
      ++flare;
    }
    logf("Flare dispatch: no free flares");
  }

  void FlareManager::updatePositions()
  {
    for (auto &flare : flarePool)
    {
      if (!flare.isActive())
        continue;

      flare.updatePosition();

      if (flare.completedCycle)
      {
        contextManager->stateManager.getPhaseEvasionGameState().flaresEvaded++;
        contextManager->stateManager.displayShouldUpdate = true;
        flare.completedCycle = false;
      }
    }
  }

  const size_t FlareManager::size() const
  {
    return std::count_if(flarePool.begin(), flarePool.end(), [](const Flare &flare)
                         { return flare.isActive(); });
  }

  void FlareManager::reset()
  {
    for (Flare &flare : flarePool)
    {
      flare.reset();
    }
  }
}