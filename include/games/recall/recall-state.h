#pragma once

#include <cstdint>

namespace Games
{
  enum class GameState
  {
    Startup,
    ComputerPlaybackOnDisplay,
    ComputerPlaybackPaused,
    Player,
    GameOver
  };

  class RecallGameState
  {
  public:
    RecallGameState() : highScore{0}, round{0} {}
    uint16_t highScore;
    uint16_t round;
    GameState current = GameState::Startup;

    void reset() { highScore = round = 0; }
  };
}