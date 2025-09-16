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
    size_t size;
    CRGB *leds;

  public:
    LedStrip(Engine::SystemConfig &configuration, Engine::RunState &state);
    CRGB *getRawColors();
    size_t getSize() const { return size * sizeof(CRGB); }
    void updateColor();
  };
}