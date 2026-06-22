#pragma once

#include "engine/layer.h"
#include "engine/timer.h"
#include "core/context-manager.h"
#include "games/chain-reaction/ion-cannon.h"

namespace Games::ChainReaction
{
  class Driver : public Engine::Layer, private Engine::Timer
  {
  public:
    Driver(SystemCore::ContextManager *ctx);
    ~Driver() { state.reset(); }
    void nextEvent() override;
    void reset();
    void renderIons();
    void advanceActiveIon();

  private:
    SystemCore::ContextManager *contextManager;
    GameState &state;
    IonCannon cannon;

    void handleDispatch();
  };
}