#pragma once

#include "engine/layer.h"
#include "engine/timer.h"
#include "core/context-manager.h"
#include "games/phase-evasion/player.h"
#include "games/phase-evasion/flare.h"
#include "games/phase-evasion/flare-manager.h"

namespace Games::PhaseEvasion
{
  class Controller : public Engine::Layer, private Engine::Timer
  {
  public:
    Controller(::Core::ContextManager *ctx);
    void nextEvent() override;
    static constexpr uint16_t playerClearance = 20;

  private:
    ::Core::ContextManager *contextManager;
    GameState &state = contextManager->stateManager.getPhaseEvasionGameState();
    Player player;
    FlareManager flareMgr;

    void getUpdates();
    void renderUserColor();
    void renderFlare();
    void checkCollision();
    void checkGrowth();
  };
}