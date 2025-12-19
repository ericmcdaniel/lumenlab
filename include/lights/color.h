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

    Color operator*(double scale) const
    {
#ifdef VIRTUALIZATION
      Color result;
      result.r = static_cast<uint8_t>(std::clamp(r * scale, 0.0, 255.0));
      result.g = static_cast<uint8_t>(std::clamp(g * scale, 0.0, 255.0));
      result.b = static_cast<uint8_t>(std::clamp(b * scale, 0.0, 255.0));
      return result;
#else
      Color result = *this;
      uint8_t brightness = static_cast<uint8_t>(std::clamp(scale * 255.0, 0.0, 255.0));
      result.nscale8_video(brightness);
      return result;
#endif
    }

    Color operator/(double) const = delete;

    Color &operator*=(double scale)
    {
#ifdef VIRTUALIZATION
      r = static_cast<uint8_t>(std::clamp(r * scale, 0.0, 255.0));
      g = static_cast<uint8_t>(std::clamp(g * scale, 0.0, 255.0));
      b = static_cast<uint8_t>(std::clamp(b * scale, 0.0, 255.0));
      return *this;
#else
      uint8_t brightness = static_cast<uint8_t>(std::clamp(scale * 255.0, 0.0, 255.0));
      nscale8_video(brightness);
      return *this;
#endif
    }

    Color saturated() const
    {
      CHSV hsv = rgb2hsv_approximate(*this);
      hsv.s = 255;

      CRGB rgb;
      hsv2rgb_rainbow(hsv, rgb);

      return Color(rgb.r, rgb.g, rgb.b);
    }
  };
}