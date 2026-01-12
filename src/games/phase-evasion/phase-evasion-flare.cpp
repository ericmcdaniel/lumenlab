#include "games/phase-evasion/phase-evasion-flare.h"

namespace Games
{
  void PhaseEvasionFlare::updatePosition()
  {
    if (isReady())
    {
      --position;
      wait(20); // TODO: variable speed
    }
  }
}