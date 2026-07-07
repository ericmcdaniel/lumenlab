#pragma once

#include <cstdint>

namespace Games::Demo
{
  enum class Actions
  {
    Active
  };

  class GameState
  {
  public:
    GameState() : highScore{0}, currentScore{0} {}
    void reset() { highScore = currentScore = 0; }

    Actions current = Actions::Active;
    uint16_t highScore;
    uint16_t currentScore;
  };
}