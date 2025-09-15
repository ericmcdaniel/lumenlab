#pragma once

#define FASTLED_INTERNAL
#include <FastLED.h>
#undef min
#undef max
#include "engine/system-config.h"
#include "engine/timeable.h"

namespace Lights
{
  class LedStrip : public Time::Timeable
  {
  private:
    const Engine::SystemConfig &config;
    unsigned int size;
    CRGB *leds;

  public:
    LedStrip(Engine::SystemConfig &configuration, Engine::RunState &state);
    void getColors();
  };
}