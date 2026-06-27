#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "core/context-manager.h"
#include "games/chain-reaction/ion-cannon.h"

namespace Games::ChainReaction
{
  class GameMain : public Engine::ApplicationRuntime, private Engine::Timer
  {
  public:
    GameMain(SystemCore::ContextManager *ctx);
    ~GameMain() { state.reset(); }
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