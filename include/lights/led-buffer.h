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
    unsigned int _size;
    CRGB *leds;

  public:
    LedBuffer(unsigned int numLeds);
    ~LedBuffer();

    CRGB &operator[](unsigned int index) { return leds[index]; }
    const CRGB &operator[](size_t index) const { return leds[index]; }

    explicit operator CRGB *() { return leds; }
    explicit operator const CRGB *() const { return leds; }

    unsigned int size() { return _size; }
  };
}