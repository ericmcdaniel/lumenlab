#pragma once

#include "games/testing-sandbox/test-player.h"
#include "player/controller.h"

namespace Games
{
  /**
   * This is not normally a playable state, but is just an arena where I can experiment with code and
   * use that to build out the other games.
   */
  class TestCore
  {
  private:
    TestPlayer *player = nullptr;
    TestPlayer *player2 = nullptr;
    Player::Controller controller;
    Lights::LedStrip &leds;

  public:
    TestCore(Engine::SystemConfig &config, Lights::LedStrip &l, const Player::Controller &gc) : controller(gc), leds(l)
    {
      player = new Games::TestPlayer{config, leds};
      player2 = new Games::TestPlayer{config, leds};
    }
    void nextEvent();
  };
}