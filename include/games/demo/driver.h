#pragma once

#include "core/context-manager.h"
#include "engine/layer.h"
#include "games/demo/player.h"

namespace Games::Demo
{
  class Driver : public Engine::Layer
  {
  public:
    Driver(SystemCore::ContextManager *ctx) : Engine::Layer{}, contextManager{ctx}, player1{Player{ctx, width}}, player2{Player{ctx, width}}
    {
      contextManager->stateManager.getDemoGameState().reset();
    }

    void nextEvent() override;
    uint16_t getCurrentScore() { return contextManager->stateManager.getDemoGameState().currentScore; }
    uint16_t getHighScore() { return contextManager->stateManager.getDemoGameState().highScore; }
    void incrementCurrentScore();
    void incrementHighScore();

  private:
    SystemCore::ContextManager *contextManager;
    Player player1;
    Player player2;
    static constexpr float speed = 4.0f;
    static constexpr uint16_t width = 7;
  };
}