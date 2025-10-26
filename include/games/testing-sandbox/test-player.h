#pragma once

#include "core/context-manager.h"
#include "games/testing-sandbox/game-state.h"
#include "player/player.h"
#include "logger.h"

namespace Games
{
  class TestPlayer : public Player::Player
  {
  private:
    Core::ContextManager *contextManager;
    int position = 0;
    int width = 7;

  public:
    TestPlayer(Core::ContextManager *ctx) : contextManager{ctx}, Player::Player{ctx->config, ctx->leds} {};
    unsigned long getPosition() { return position; }
    void move(const int distance);
    void updatePlayer1LedBuffer();
    void updatePlayer2LedBuffer();
  };
}