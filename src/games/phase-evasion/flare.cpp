#include "games/phase-evasion/flare.h"

namespace Games::PhaseEvasion
{
  void Flare::updatePosition()
  {
    positionFloat -= speed;
  }
}