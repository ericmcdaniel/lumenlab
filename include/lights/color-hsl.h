#pragma once

#include <FastLED.h>
#include <cstdint>
#include "color.h"

namespace Lights
{

  class ColorHsl
  {
  public:
    ColorHsl() : hslValues{0, 0, 0} {}
    ColorHsl(uint8_t hue, uint8_t saturation, uint8_t lightness) : hslValues{hue, saturation, lightness} {}

    uint8_t &hue();
    uint8_t &saturation();
    uint8_t &lightness();

    const uint8_t &hue() const;
    const uint8_t &saturation() const;
    const uint8_t &lightness() const;

    static ColorHsl fromRgb(uint8_t red, uint8_t green, uint8_t blue);
    static ColorHsl fromRgb(Color color);

    Color toColor() const;

  private:
    CHSV hslValues;
    static ColorHsl convertFromRgb(uint8_t red, uint8_t green, uint8_t blue);
  };

}
