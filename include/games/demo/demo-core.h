#pragma once

#include "core/context-manager.h"
#include "engine/layer.h"
#include "games/demo/demo-player.h"

namespace Games
{
  class DemoCore : public Engine::Layer
  {
  public:
    DemoCore(Core::ContextManager *ctx) : Engine::Layer{}, contextManager{ctx}, player1{DemoPlayer{ctx}}, player2{DemoPlayer{ctx}}
    {
      contextManager->stateManager.getDemoGameState().reset();
    }

    void nextEvent() override;
    uint16_t getCurrentScore() { return contextManager->stateManager.getDemoGameState().currentScore; }
    uint16_t getHighScore() { return contextManager->stateManager.getDemoGameState().highScore; }
    void incrementCurrentScore();
    void incrementHighScore();

  private:
    Core::ContextManager *contextManager;
    DemoPlayer player1;
    DemoPlayer player2;
    static constexpr float speed = 4.0f;
  };
}