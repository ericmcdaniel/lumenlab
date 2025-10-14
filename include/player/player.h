#pragma once

#include "player/controller.h"
#include "engine/timer.h"
#include "engine/system-config.h"
#include "lights/led-strip.h"

namespace Player
{
  class Player
  {
  private:
    const Engine::SystemConfig &config;
    Lights::LedStrip &leds;

  public:
    Player(Engine::SystemConfig &configuration,
           Lights::LedStrip &leds) : config{configuration},
                                     leds{leds} {};
  };
}