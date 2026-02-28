#pragma once

#include <cstdint>

#include "core/configuration.h"
#include "lights/color.h"

namespace Lights
{
  class LedBuffer
  {
  public:
    LedBuffer() : leds{new Color[maxLEDs]} {}
    ~LedBuffer() { delete leds; }
    LedBuffer(LedBuffer &&other) = delete;
    LedBuffer &operator=(LedBuffer &&other) = delete;
    LedBuffer(const LedBuffer &other) = delete;
    LedBuffer &operator=(const LedBuffer &other) = delete;

    Color &operator[](uint16_t index) { return leds[index]; }
    const Color &operator[](uint16_t index) const { return leds[index]; }

    explicit operator Color *() { return leds; }
    explicit operator const Color *() const { return leds; }

    uint16_t size() { return SystemCore::Configuration::numLeds(); }

  private:
    Color *leds;
    static constexpr uint16_t maxLEDs = 600;
  };
}