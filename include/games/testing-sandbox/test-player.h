#pragma once

#include "player/player.h"

namespace TestingSandbox
{
  class TestPlayer : public Player::Player
  {
  private:
    unsigned int position;
    // unsigned int color;
    Engine::RunState runType = Engine::RunState::GAME_SANDBOX;

  public:
    TestPlayer(Engine::SystemConfig &configuration, Lights::LedStrip &leds) : Player::Player{configuration, runType, leds}, position{0} {};
  };
}