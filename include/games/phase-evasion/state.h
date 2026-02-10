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
    GameState() : highScore{0}, flaresEvaded{0}, gemsCaptured{0} {}
    uint16_t flaresEvaded;
    uint16_t gemsCaptured;
    uint16_t highScore;
    Actions current = Actions::Startup;

    void reset()
    {
      highScore = flaresEvaded = gemsCaptured = 0;
      // highScore = contextManager->memory.getUInt("phase-evasion-high-score");
    }
    uint16_t calculateTotalScore() const { return flaresEvaded + (2 * gemsCaptured); }
  };
}