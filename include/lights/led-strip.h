#pragma once

#define FASTLED_INTERNAL
#include <FastLED.h>
#undef min
#undef max

#include "engine/system-config.h"
#include "engine/timeable.h"
#include "lights/led-buffer.h"
#include "lights/led-luminance.h"

namespace Lights
{
  class LedStrip : public Time::Timeable
  {
  private:
    const Engine::SystemConfig &config;
    unsigned int _size;
    LedLuminance luminance;

  public:
    LedBuffer buffer;
    LedStrip(Engine::SystemConfig &configuration, Engine::RunState &state);
    CRGB *getRawColors();

    unsigned int size() const { return _size; }
    void updateColor();
    void setDefault();
    void adjustLuminance();
  };
}