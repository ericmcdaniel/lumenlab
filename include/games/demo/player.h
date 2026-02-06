#pragma once

#include "core/context-manager.h"
#include "player/player.h"

namespace Games::Demo
{
  class Player : public ::Player::BasePlayer
  {
  public:
    Player(SystemCore::ContextManager *ctx, const uint16_t width) : ::Player::BasePlayer{ctx, width} {};
    void updatePlayer1LedBuffer();
    void updatePlayer2LedBuffer();
  };
}