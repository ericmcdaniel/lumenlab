#include "games/phase-evasion/flare.h"

namespace Games::PhaseEvasion
{
  void Flare::updatePosition()
  {
    if (positionFloat <= 0)
    {
      active = false;
    }
    else
    {
      positionFloat -= speed;
    }
  }

  void Flare::activate()
  {
    active = true;
    positionFloat = static_cast<float>(SystemCore::Configuration::numLeds + width);
  }

  void Flare::deactivate()
  {
    active = false;
  }
}