#pragma once

#include "core/context-manager.h"
#include "player/player.h"

namespace Games::Demo
{
  class Player : public ::Player::Player
  {
  public:
    Player(SystemCore::ContextManager *ctx, const uint16_t width) : ::Player::Player{ctx, width} {};
    void updatePlayer1LedBuffer();
    void updatePlayer2LedBuffer();
  };
}