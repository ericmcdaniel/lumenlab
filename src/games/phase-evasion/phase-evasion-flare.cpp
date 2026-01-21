#include "games/phase-evasion/phase-evasion-flare.h"

namespace Games
{
  void PhaseEvasionFlare::updatePosition()
  {
    positionFloat -= speed;
  }
}