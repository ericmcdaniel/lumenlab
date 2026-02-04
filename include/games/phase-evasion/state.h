#pragma once

#include <cstdint>

namespace Games::PhaseEvasion
{
  enum class Actions
  {
    Startup,
    ActiveGame,
    WindDown,
    MuzzleFlash,
    GameOver
  };

  class GameState
  {
  public:
    GameState() : highScore{0}, flaresEvaded{0} {}
    uint16_t highScore;
    uint16_t flaresEvaded;
    Actions current = Actions::Startup;
    void reset() { highScore = flaresEvaded = 0; }
  };
}