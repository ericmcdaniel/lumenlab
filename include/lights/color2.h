#pragma once

#include <algorithm>
#include <FastLED.h>
#include "lights/color-code2.h"
#include <cstdint>

namespace Lights
{
  class Color2 : public CRGB
  {
  public:
    using CRGB::CRGB;
    Color2() : CRGB() {}
    Color2(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : CRGB(red, green, blue), a{alpha} {}
    Color2(ColorCode2 color) : CRGB{static_cast<uint32_t>(color)} {}

    uint8_t a;

    Color2 operator*(double scale) const;
    Color2 operator*(uint8_t scale) const;
    Color2 operator/(double scale) const;
    Color2 operator/(uint8_t scale) const;
    Color2 &operator*=(double scale);
  };

  inline const Color2 colorPalette[4] = {
      Color(ColorCode2::ThemeBlue),
      Color(ColorCode2::ThemeRed),
      Color(ColorCode2::ThemeGreen),
      Color(ColorCode2::ThemeYellow)};
}