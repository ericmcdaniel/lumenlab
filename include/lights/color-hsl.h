#pragma once

#include <FastLED.h>
#include <cstdint>
#include "color.h"

namespace Lights
{

  class ColorHsl
  {
  public:
    ColorHsl();
    ColorHsl(uint8_t hue, uint8_t saturation, uint8_t lightness);

    uint8_t &hue();
    uint8_t &saturation();
    uint8_t &lightness();

    const uint8_t &hue() const;
    const uint8_t &saturation() const;
    const uint8_t &lightness() const;

    static ColorHsl fromRGB(uint8_t red, uint8_t green, uint8_t blue);

    Color toColor() const;

  private:
    CHSV hslValues;
  };

}
