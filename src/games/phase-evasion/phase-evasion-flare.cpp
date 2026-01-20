#include "games/phase-evasion/phase-evasion-flare.h"

namespace Games
{
  void PhaseEvasionFlare::updatePosition()
  {
    if (isReady())
    {
      positionFloat -= speed;
      wait(1); // TODO: variable speed
    }
  }
}