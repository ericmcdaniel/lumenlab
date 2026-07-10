#pragma once

#include "platform/context-manager.h"
#include "engine/application-runtime.h"
#include "games/demo/player.h"

namespace Games::Demo
{
  class GameMain : public Engine::ApplicationRuntime
  {
  public:
    GameMain(SystemCore::ContextManager *ctx) : Engine::ApplicationRuntime{},
                                                state{ctx->stateManager.getDemoGameState()},
                                                contextManager{ctx},
                                                player1{Player{ctx, width, ColorPalette::Red}},
                                                player2{Player{ctx, width, ColorPalette::Blue}}
    {
      state.reset();
    }

    void nextEvent() override;
    void incrementCurrentScore();
    void incrementHighScore();

    static constexpr uint16_t width = 7;

  private:
    SystemCore::ContextManager *contextManager;
    GameState state;
    Player player1;
    Player player2;
    static constexpr float speed = 4.0f;

    void readInput();
    void updatePosition();
    void render();
  };
}