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
    Controller(SystemCore::ContextManager *ctx);
    void nextEvent() override;
    static constexpr uint16_t playerClearance = 25;
    static constexpr uint16_t playerWidth = 5;
    static constexpr uint32_t intermissionDelay = 10'000;

  private:
    SystemCore::ContextManager *contextManager;
    Engine::Timer intermissionTimer;
    GameState &state = contextManager->stateManager.getPhaseEvasionGameState();
    Player player;
    FlareManager flareManager;
    uint32_t interval = 2000;
    uint32_t gap = 1500;
    float speed = 0.4f;

    void getUpdates();
    void renderPlayer();
    void renderFlare();
    void checkCollision();
    void orchestrateCollection();
    void gameOver();
  };
}