#pragma once

#include <cstdint>

namespace Games
{
  enum class ActivePlayer
  {
    Computer,
    Player,
    None
  };

  class RecallGameState
  {
  public:
    RecallGameState() : highScore{0}, round{0} {}
    void reset() { highScore = round = 0; }
    uint16_t highScore;
    uint16_t round;
  };
}