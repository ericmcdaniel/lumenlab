#pragma once

#include "platform/context-manager.h"
#include "engine/application-runtime.h"
#include "games/demo/player.h"

namespace Games::Demo
{
  class GameMain : public Engine::ApplicationRuntime
  {
  public:
    GameMain(SystemCore::ContextManager *ctx) : Engine::ApplicationRuntime{}, contextManager{ctx}, player1{Player{ctx, width}}, player2{Player{ctx, width}}
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