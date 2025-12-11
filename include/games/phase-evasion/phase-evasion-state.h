#pragma once

#include <cstdint>

namespace Games
{
  class PhaseEvasionGameState
  {
  public:
    PhaseEvasionGameState() : highScore{0}, spectersDodged{0} {}
    void reset() { highScore = spectersDodged = 0; }
    uint16_t highScore;
    uint16_t spectersDodged;
  };
}