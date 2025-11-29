#pragma once

#include "core/context-manager.h"
#include "player/player.h"

namespace Games
{
  class DemoPlayer : public Player::Player
  {
  public:
    DemoPlayer(Core::ContextManager *ctx) : contextManager{ctx}, Player::Player{ctx} {};
    uint16_t getPosition() { return position; }
    void move(const int distance);
    void updatePlayer1LedBuffer();
    void updatePlayer2LedBuffer();

  private:
    Core::ContextManager *contextManager;
    uint16_t position = 0;
    float positionPrecise = 0.0f;
    static constexpr uint16_t width = 7;
  };
}