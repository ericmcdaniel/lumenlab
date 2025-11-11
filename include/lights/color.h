#pragma once

#ifdef RELEASE
#define FASTLED_INTERNAL
#include <FastLED.h>
#undef min
#undef max
#else
#include "debug-fastled.h"
#endif

#include <cstdint>

namespace Lights
{
  class Color
  {
  public:
    Color() : colors{CRGB{}} {}
    Color(uint8_t red, uint8_t green, uint8_t blue) : colors{CRGB{red, green, blue}} {}

    uint8_t &r() { return colors.r; }
    uint8_t &g() { return colors.g; }
    uint8_t &b() { return colors.b; }

    const uint8_t &r() const { return colors.r; }
    const uint8_t &g() const { return colors.g; }
    const uint8_t &b() const { return colors.b; }

  private:
    CRGB colors;
  };
}