#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "core/context-manager.h"
#include "games/reflex/signal.h"

namespace Games::Reflex
{
  class GameMain : public Engine::ApplicationRuntime, private Engine::Timer
  {
  public:
    GameMain(SystemCore::ContextManager *ctx);
    ~GameMain() { state.reset(); }
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