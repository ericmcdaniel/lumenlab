#pragma once

#include "engine/layer.h"
#include "engine/timer.h"
#include "core/context-manager.h"

namespace Games::ChainReaction
{
  class Driver : public Engine::Layer, private Engine::Timer
  {
  public:
    Driver(SystemCore::ContextManager *ctx);
    ~Driver() { state.reset(); }

  private:
    SystemCore::ContextManager *contextManager;
    GameState &state;
  };
}