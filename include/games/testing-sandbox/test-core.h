#pragma once

#include "core/context-manager.h"
#include "engine/layer.h"
#include "games/testing-sandbox/test-player.h"

namespace Games
{
  class TestCore : public Engine::Layer
  {
  public:
    TestCore(Core::ContextManager *ctx) : Engine::Layer{}, contextManager{ctx}
    {
      player1 = new Games::TestPlayer{contextManager};
      player2 = new Games::TestPlayer{contextManager};
      contextManager->stateManager.getSandboxGameState().reset();
    }

    ~TestCore()
    {
      delete player1;
      delete player2;
    }

    void nextEvent() override;
    uint16_t getCurrentScore() { return contextManager->stateManager.getSandboxGameState().currentScore; }
    uint16_t getHighScore() { return contextManager->stateManager.getSandboxGameState().highScore; }
    void incrementCurrentScore();
    void incrementHighScore();

  private:
    Core::ContextManager *contextManager;
    TestPlayer *player1 = nullptr;
    TestPlayer *player2 = nullptr;
  };
}