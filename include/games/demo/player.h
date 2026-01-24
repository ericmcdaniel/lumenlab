#pragma once

#include "core/context-manager.h"
#include "player/player.h"

namespace Games::Demo
{
  class Player : public ::Player::Player
  {
  public:
    Player(SystemCore::ContextManager *ctx) : contextManager{ctx}, ::Player::Player{ctx} {};
    void updatePlayer1LedBuffer();
    void updatePlayer2LedBuffer();

  private:
    SystemCore::ContextManager *contextManager;
    static constexpr uint16_t width = 7;
  };
}