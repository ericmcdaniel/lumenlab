#pragma once

#include <cstdint>

namespace SystemCore
{
  class ContextManager;
}

namespace Games::ChainReaction
{
  enum class Actions
  {
    Startup,
    ActiveGame,
    GameOver
  };

  class GameState
  {
  public:
    GameState(SystemCore::ContextManager *ctx) : contextManager{ctx} {}
    // uint16_t scores (tbd)
    Actions current = Actions::Startup;
    static constexpr const char *memoryKeyName = "chain-high";

    void reset();

  private:
    SystemCore::ContextManager *contextManager;
  };
}