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
    static constexpr uint16_t playerOffset = 25;
    static constexpr uint16_t playerWidth = 5;
    static constexpr uint32_t windDownLength = 30'000;

  private:
    SystemCore::ContextManager *contextManager;
    Engine::Timer windDownTimer;
    GameState &state = contextManager->stateManager.getPhaseEvasionGameState();
    Player player;
    FlareManager flareManager;
    float interval;
    float gap;
    float speed;

    void getUpdates();
    void renderPlayer();
    void renderFlare();
    void checkCollision();
    void orchestrateCollection();
    void gameOver();
    void reset();
  };
}