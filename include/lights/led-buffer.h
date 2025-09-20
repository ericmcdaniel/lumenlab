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
    LedBuffer(unsigned int numLeds) : _size{numLeds}, leds{new CRGB[numLeds]} {}
    LedBuffer() { delete leds; }

    LedBuffer(const LedBuffer &other) : _size(other._size), leds(new CRGB[other._size])
    {
      for (unsigned int i = 0; i < _size; ++i)
      {
        leds[i] = other.leds[i];
      }
    }

    LedBuffer &operator=(const LedBuffer &other)
    {
      if (this != &other)
      {
        CRGB *newLeds = new CRGB[other._size];
        for (unsigned int i = 0; i < other._size; ++i)
        {
          newLeds[i] = other.leds[i];
        }

        delete[] leds;
        leds = newLeds;
        _size = other._size;
      }
      return *this;
    }

    LedBuffer(LedBuffer &&other) = delete;
    LedBuffer &operator=(LedBuffer &&other) = delete;

    CRGB &operator[](unsigned int index) { return leds[index]; }
    const CRGB &operator[](unsigned int index) const { return leds[index]; }

    explicit operator CRGB *() { return leds; }
    explicit operator const CRGB *() const { return leds; }

    unsigned int size() { return _size; }
  };
}