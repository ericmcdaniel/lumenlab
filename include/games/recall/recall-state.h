#pragma once

#include <cstdint>

namespace Games
{
  enum class RecallStates
  {
    Startup,
    ComputerPlaybackOnDisplay,
    ComputerPlaybackPaused,
    PlayerResponseEvaluation,
    PlayerResponseVerified,
    GameOver
  };

  class RecallGameState
  {
  public:
    RecallGameState() : highScore{0}, round{0} {}
    uint16_t highScore;
    uint16_t round;
    RecallStates current = RecallStates::Startup;

    void reset() { highScore = round = 0; }
  };
}