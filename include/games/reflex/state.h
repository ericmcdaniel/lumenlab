#pragma once

#include <cstdint>

namespace SystemCore
{
  class ContextManager;
}

namespace Games::Reflex
{
  enum class Actions
  {
    Startup,
    Ready,
    ActiveGame,
    GameOver
  };

  class GameState
  {
  public:
    GameState(SystemCore::ContextManager *ctx) : contextManager{ctx} {}

    Actions current = Actions::Startup;
    static constexpr const char *memoryKeyName = "high_reflex";

    void reset() {}

  private:
    SystemCore::ContextManager *contextManager;
  };
}