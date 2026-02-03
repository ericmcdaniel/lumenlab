#pragma once

#include "core/context-manager.h"
#include "player/player.h"

namespace Games::PhaseEvasion
{
  class Player : public ::Player::Player
  {
  public:
    Player(SystemCore::ContextManager *ctx, uint16_t w) : ::Player::Player{ctx}, contextManager{ctx}, width{w} {};
    void checkColorChangeRequest();
    Lights::Color getColor() { return currentColor; }
    const uint16_t width;

  private:
    SystemCore::ContextManager *contextManager;
    Lights::Color currentColor;
  };
}