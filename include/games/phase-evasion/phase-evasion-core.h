#pragma once

#include "engine/layer.h"
#include "engine/timer.h"
#include "core/context-manager.h"
#include "games/phase-evasion/phase-evasion-player.h"
#include "games/phase-evasion/phase-evasion-flare.h"
#include "games/phase-evasion/phase-evasion-flare-manager.h"

namespace Games
{
  class PhaseEvasionCore : public Engine::Layer, private Engine::Timer
  {
  public:
    PhaseEvasionCore(Core::ContextManager *ctx);
    void nextEvent() override;
    static constexpr uint16_t playerClearance = 20;

  private:
    Core::ContextManager *contextManager;
    PhaseEvasionGameState &state = contextManager->stateManager.getPhaseEvasionGameState();
    PhaseEvasionPlayer player;
    PhaseEvasionFlareManager flareMgr;

    void getUpdates();
    void renderUserColor();
    void renderFlare();
    void checkCollision();
  };
}