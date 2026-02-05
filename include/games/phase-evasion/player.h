#pragma once

#include "core/context-manager.h"
#include "player/player.h"

namespace Games::PhaseEvasion
{
  class Player : public ::Player::Player
  {
  public:
    Player(SystemCore::ContextManager *ctx, uint16_t width) : ::Player::Player{ctx, width} {};
    void checkColorChangeRequest();
    Lights::Color getColor() { return currentColor; }

  private:
    Lights::Color currentColor;
  };
}