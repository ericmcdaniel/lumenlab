#pragma once

#include <cstdint>

#include "platform/configuration.h"
#include "lights/color2.h"

namespace Lights
{
  class LedBuffer2
  {
  public:
    LedBuffer2() : leds{new Color2[maxLEDs]} {}
    ~LedBuffer2() { delete[] leds; }
    LedBuffer2(LedBuffer2 &&other) = delete;
    LedBuffer2 &operator=(LedBuffer2 &&other) = delete;
    LedBuffer2(const LedBuffer2 &other) = delete;
    LedBuffer2 &operator=(const LedBuffer2 &other) = delete;

    Color2 &operator[](uint16_t index) { return leds[index]; }
    const Color2 &operator[](uint16_t index) const { return leds[index]; }

    explicit operator Color2 *() { return leds; }
    explicit operator const Color2 *() const { return leds; }

    uint16_t size() { return SystemCore::Configuration::numLeds(); }

  private:
    Color2 *leds;
    static constexpr uint16_t maxLEDs = 600;
  };
}