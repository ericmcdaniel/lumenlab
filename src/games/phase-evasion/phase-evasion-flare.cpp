#include "games/phase-evasion/phase-evasion-flare.h"

namespace Games
{
  void PhaseEvasionFlare::updatePosition()
  {
    if (isReady())
    {
      --position;
      wait(15); // TODO: variable speed
    }
  }
}