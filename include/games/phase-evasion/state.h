#pragma once

#include <cstdint>

namespace SystemCore
{
  class ContextManager;
}

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
    GameState(SystemCore::ContextManager *ctx) : contextManager{ctx}, highScore{0}, flaresEvaded{0}, gemsCaptured{0} {}
    uint16_t flaresEvaded;
    uint16_t gemsCaptured;
    uint16_t highScore;
    Actions current = Actions::Startup;
    static constexpr const char *memoryKeyName = "phase-high";

    void reset();
    uint16_t calculateTotalScore() const;
    void updateHighScore();

  private:
    SystemCore::ContextManager *contextManager;
  };
}