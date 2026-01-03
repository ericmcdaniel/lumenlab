#pragma once

#include <cstdint>

namespace Games
{
  enum class PhaseEvasionStates
  {
    Startup,
    ActiveGame
  };

  class PhaseEvasionGameState
  {
  public:
    PhaseEvasionGameState() : highScore{0}, spectersDodged{0} {}
    uint16_t highScore;
    uint16_t spectersDodged;
    PhaseEvasionStates current = PhaseEvasionStates::Startup;
    void reset() { highScore = spectersDodged = 0; }
  };
}