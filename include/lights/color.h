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
    CRGB colors;

  private:
  };
}