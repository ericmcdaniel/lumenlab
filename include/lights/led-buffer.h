#pragma once

#define FASTLED_INTERNAL
#include <FastLED.h>
#undef min
#undef max

#include "engine/system-config.h"

namespace Lights
{
  class LedBuffer
  {
  private:
    unsigned int size;

  public:
    LedBuffer(unsigned int size);
    ~LedBuffer();
    CRGB *leds;
  };
}