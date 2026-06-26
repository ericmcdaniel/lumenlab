#pragma once

#include "engine/layer.h"
#include "engine/timer.h"
#include "core/context-manager.h"
#include "games/reflex/signal.h"

namespace Games::Reflex
{
  class Driver : public Engine::Layer, private Engine::Timer
  {
  public:
    Driver(SystemCore::ContextManager *ctx);
    ~Driver() { state.reset(); }
    static constexpr uint16_t signalWidth = 7;
    static constexpr float signalSpeed = 1.0f;
    void nextEvent() override;
    void renderSignal();
    void reset();

  private:
    SystemCore::ContextManager *contextManager;
    GameState &state;

    Signal signal;
  };
}