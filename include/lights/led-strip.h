#pragma once

#include <FastLED.h>
#include "timeable.h"
#include "engine/system-config.h"

namespace Lights
{

  class LedStrip : protected Time::Timeable
  {
  private:
    const Engine::SystemConfig &config;
    unsigned int size;
    CRGB *leds;

  public:
    LedStrip(Engine::SystemConfig &configuration);
    void getColors();
  };
}