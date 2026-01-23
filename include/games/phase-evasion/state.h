#pragma once

#include <cstdint>

namespace Games::PhaseEvasion
{
  enum class Actions
  {
    Startup,
    ActiveGame,
    GameOver
  };

  class GameState
  {
  public:
    GameState() : highScore{0}, spectersDodged{0} {}
    uint16_t highScore;
    uint16_t spectersDodged;
    Actions current = Actions::Startup;
    void reset() { highScore = spectersDodged = 0; }
  };
}