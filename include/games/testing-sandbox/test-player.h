#pragma once

#include "player/player.h"
#include "logger.h"

namespace Games
{
  class TestPlayer : public Player::Player
  {
  private:
    int pos;
    int width = 7;
    Lights::LedStrip &leds;
    // unsigned int color;

  public:
    TestPlayer(Engine::SystemConfig &configuration, Lights::LedStrip &l) : Player::Player{configuration, leds}, pos{0}, leds{l} {};
    unsigned long position() { return pos; }
    void move(const int distance);
    void updateLedBuffer();
    void updateLedBuffer2();
  };
}