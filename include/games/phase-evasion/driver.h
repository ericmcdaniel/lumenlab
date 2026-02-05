#pragma once

#include "engine/layer.h"
#include "engine/timer.h"
#include "core/context-manager.h"
#include "games/phase-evasion/player.h"
#include "games/phase-evasion/flare.h"
#include "games/phase-evasion/flare-manager.h"
#include "games/phase-evasion/gem.h"

namespace Games::PhaseEvasion
{
  class Driver : public Engine::Layer, private Engine::Timer
  {
  public:
    Driver(SystemCore::ContextManager *ctx);
    void nextEvent() override;
    static constexpr uint16_t playerOffset = 25;
    static constexpr uint16_t playerWidth = 5;
    static constexpr uint32_t windDownLength = 20'000;

  private:
    SystemCore::ContextManager *contextManager;
    Engine::Timer windDownTimer;
    GameState &state = contextManager->stateManager.getPhaseEvasionGameState();
    Player player;
    FlareManager flareManager;
    Gem gem;

    float interval;
    float gap;
    float speed;

    void getUpdates();
    void renderPlayer();
    void renderFlare();
    void renderGem();
    void checkCollision();
    void checkGemCapture();
    void checkChallenge();
    void muzzleFlash();
    void gameOver();
    void reset();
  };
}