#pragma once

#include "engine/layer.h"
#include "engine/timer.h"
#include "core/context-manager.h"
#include "games/phase-evasion/phase-evasion-player.h"
#include "games/phase-evasion/phase-evasion-flare.h"

namespace Games
{
  class PhaseEvasionCore : public Engine::Layer, private Engine::Timer
  {
  public:
    PhaseEvasionCore(Core::ContextManager *ctx);
    void nextEvent() override;
    static constexpr uint16_t clearance = 15;

  private:
    Core::ContextManager *contextManager;
    PhaseEvasionGameState &state = contextManager->stateManager.getPhaseEvasionGameState();
    PhaseEvasionPlayer player;
    PhaseEvasionFlare flare;
    void renderUserColor();
    void renderFlare();
    void checkCollision();
  };
}