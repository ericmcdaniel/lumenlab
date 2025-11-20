#pragma once

#include <FastLED.h>
#include <cstdint>
#include "color.h"

namespace Lights
{
  class ColorHsl : public CHSV
  {
  public:
    ColorHsl() : CHSV{0, 0, 0} {}
    ColorHsl(uint8_t hue, uint8_t saturation, uint8_t lightness) : CHSV{hue, saturation, lightness} {}

    static ColorHsl fromRgb(uint8_t red, uint8_t green, uint8_t blue);
    static ColorHsl fromRgb(Color color);

    Color toColor() const;

  private:
    static ColorHsl convertFromRgb(uint8_t red, uint8_t green, uint8_t blue);
  };
}
