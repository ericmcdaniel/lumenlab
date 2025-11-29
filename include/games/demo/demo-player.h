#pragma once

#include "core/context-manager.h"
#include "player/player.h"

namespace Games
{
  class DemoPlayer : public Player::Player
  {
  public:
    DemoPlayer(Core::ContextManager *ctx) : contextManager{ctx}, Player::Player{ctx} {};
    uint32_t getPosition() { return position; }
    void move(const int distance);
    void updatePlayer1LedBuffer();
    void updatePlayer2LedBuffer();

  private:
    Core::ContextManager *contextManager;
    int position = 0;
    static constexpr int width = 7;
  };
}