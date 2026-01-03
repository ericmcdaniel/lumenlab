#pragma once

#include <algorithm>
#include <FastLED.h>
#include "lights/color-code.h"
#include <cstdint>

namespace Lights
{
  class Color : public CRGB
  {
  public:
    using CRGB::CRGB;
    Color() : CRGB() {}
    Color(uint8_t red, uint8_t green, uint8_t blue) : CRGB(red, green, blue) {}
    Color(ColorCode color) : CRGB{static_cast<uint32_t>(color)} {}

    Lights::Color operator*(double scale) const
    {
      Color result;
      result.r = static_cast<uint8_t>(std::clamp(r * scale, 0.0, 255.0));
      result.g = static_cast<uint8_t>(std::clamp(g * scale, 0.0, 255.0));
      result.b = static_cast<uint8_t>(std::clamp(b * scale, 0.0, 255.0));
      return result;
    }

    Lights::Color operator*(uint8_t scale) const
    {
      Color result;
      result.r = (r * scale) / 255;
      result.g = (g * scale) / 255;
      result.b = (b * scale) / 255;
      return result;
    }

    Lights::Color operator/(double scale) const
    {
      Color result;
      result.r = static_cast<uint8_t>(std::clamp(r / scale, 0.0, 255.0));
      result.g = static_cast<uint8_t>(std::clamp(g / scale, 0.0, 255.0));
      result.b = static_cast<uint8_t>(std::clamp(b / scale, 0.0, 255.0));
      return result;
    }

    Lights::Color operator/(uint8_t scale) const
    {
      Color result;
      result.r = (r / scale) / 255;
      result.g = (g / scale) / 255;
      result.b = (b / scale) / 255;
      return result;
    }

    Lights::Color &operator*=(double scale)
    {
      r = static_cast<uint8_t>(std::clamp(r * scale, 0.0, 255.0));
      g = static_cast<uint8_t>(std::clamp(g * scale, 0.0, 255.0));
      b = static_cast<uint8_t>(std::clamp(b * scale, 0.0, 255.0));
      return *this;
    }
  };
}