#pragma once

#include <cstdint>

#ifdef RELEASE
#define FASTLED_INTERNAL
#include <FastLED.h>
#undef min
#undef max
#else
#include "debug-fastled.h"
#endif

namespace Lights
{
  class LedBuffer
  {
  public:
    LedBuffer(uint16_t numLeds) : _size{numLeds}, leds{new CRGB[numLeds]} {}
    LedBuffer() { delete leds; }
    LedBuffer(LedBuffer &&other) = delete;
    LedBuffer &operator=(LedBuffer &&other) = delete;

    LedBuffer(const LedBuffer &other) : _size(other._size), leds(new CRGB[other._size])
    {
      for (uint16_t i = 0; i < _size; ++i)
      {
        leds[i] = other.leds[i];
      }
    }

    LedBuffer &operator=(const LedBuffer &other)
    {
      if (this != &other)
      {
        CRGB *newLeds = new CRGB[other._size];
        for (uint16_t i = 0; i < other._size; ++i)
        {
          newLeds[i] = other.leds[i];
        }

        delete[] leds;
        leds = newLeds;
        _size = other._size;
      }
      return *this;
    }

    CRGB &operator[](uint16_t index) { return leds[index]; }
    const CRGB &operator[](uint16_t index) const { return leds[index]; }

    explicit operator CRGB *() { return leds; }
    explicit operator const CRGB *() const { return leds; }

    uint16_t size() { return _size; }

  private:
    uint16_t _size;
    CRGB *leds;
  };
}