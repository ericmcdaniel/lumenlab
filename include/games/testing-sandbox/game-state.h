#pragma once

#include <cstdint>

namespace Games
{
  class SandboxGameState
  {
  public:
    SandboxGameState() : highScore{0}, currentScore{0} {}
    void reset() { highScore = currentScore = 0; }
    uint16_t highScore;
    uint16_t currentScore;
  };
}