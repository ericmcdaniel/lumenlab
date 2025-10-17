#pragma once

#ifdef RELEASE
#define FASTLED_INTERNAL
#include <FastLED.h>
#undef min
#undef max
#else
#include "debug-fastled.h"
#endif

#include "engine/system-config.h"
#include "lights/led-buffer.h"
#include "lights/led-luminance.h"

namespace Lights
{
  class LedStrip
  {
  private:
    const Engine::SystemConfig &config;
    unsigned int _size;
    LedLuminance luminance;

  public:
    LedBuffer buffer;
    LedStrip(Engine::SystemConfig &configuration);
    CRGB *getRawColors();

    unsigned int size() const { return _size; }
    void reset();
    void adjustLuminance();
  };
}