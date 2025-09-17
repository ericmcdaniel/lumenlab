#pragma once

#include "player/game-controller.h"
#include "engine/timeable.h"
#include "engine/system-config.h"
#include "lights/led-strip.h"

namespace Player
{
  class Player : public Time::Timeable
  {
  private:
    const Engine::SystemConfig &config;
    Lights::LedStrip &leds;

  public:
    GameController controller;
    Player(Engine::SystemConfig &configuration, Engine::RunState &state, Lights::LedStrip &leds);
    void processGameController();
  };
}