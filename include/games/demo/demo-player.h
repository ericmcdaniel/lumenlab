#pragma once

#include "core/context-manager.h"
#include "player/player.h"

namespace Games
{
  class DemoPlayer : public Player::Player
  {
  public:
    DemoPlayer(Core::ContextManager *ctx) : contextManager{ctx}, Player::Player{ctx} {};
    void updatePlayer1LedBuffer();
    void updatePlayer2LedBuffer();

  private:
    Core::ContextManager *contextManager;
    static constexpr uint16_t width = 7;
  };
}