#pragma once

#include <cstdint>

namespace Games::Recall
{
  enum class Actions
  {
    Startup,
    ComputerPlaybackOnDisplay,
    ComputerPlaybackPaused,
    PlayerResponseEvaluation,
    PlayerResponseVerified,
    GameOver
  };

  class GameState
  {
  public:
    GameState() : highScore{0}, round{0} {}
    uint16_t highScore;
    uint16_t round;
    Actions current = Actions::Startup;

    void reset() { highScore = round = 0; }
  };
}