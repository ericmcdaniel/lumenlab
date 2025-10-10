#pragma once

#include "player/controller.h"
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
    Player(Engine::SystemConfig &configuration,
           Lights::LedStrip &leds) : Time::Timeable{},
                                     config{configuration},
                                     leds{leds} {};
  };
}