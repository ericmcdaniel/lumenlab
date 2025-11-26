#pragma once

#include <cstdint>

namespace Games
{
  class PhaseEvasionGameState
  {
  public:
    PhaseEvasionGameState() : highScore{0}, currentScore{0} {}
    void reset() { highScore = currentScore = 0; }
    uint16_t highScore;
    uint16_t currentScore;
  };
}