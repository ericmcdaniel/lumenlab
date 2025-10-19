#pragma once

#include "games/testing-sandbox/game-state.h"
#include "player/player.h"
#include "logger.h"

namespace Games
{
  class TestPlayer : public Player::Player
  {
  private:
    Games::SandboxGameState &state;
    Lights::LedStrip &leds;
    int position;
    int width = 7;
    // unsigned int color;

  public:
    TestPlayer(Engine::SystemConfig &c, Games::SandboxGameState &s, Lights::LedStrip &l) : Player::Player{c, leds}, position{0}, leds{l}, state{s} {};
    unsigned long getPosition() { return position; }
    void move(const int distance);
    void updateLedBuffer();
    void updateLedBuffer2();
  };
}