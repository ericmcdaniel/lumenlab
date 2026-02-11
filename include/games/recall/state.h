#pragma once

#include <cstdint>

namespace SystemCore
{
  class ContextManager;
}

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
    GameState(SystemCore::ContextManager *ctx) : contextManager{ctx}, highScore{0}, round{0} {}
    uint16_t highScore;
    uint16_t round;
    Actions current = Actions::Startup;
    static constexpr const char *memoryKeyName = "recall-high";

    void reset();
    void updateHighScore(uint16_t score);

  private:
    SystemCore::ContextManager *contextManager;
  };
}