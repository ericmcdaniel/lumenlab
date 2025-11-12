#pragma once

#include <algorithm>

#ifdef RELEASE
#define FASTLED_INTERNAL
#include <FastLED.h>
#undef min
#undef max
#else
#include "debug-fastled.h"
#endif

#include <cstdint>

namespace Lights
{
  class Color
  {
  public:
    Color() : colors{CRGB{}} {}
    Color(uint8_t red, uint8_t green, uint8_t blue) : colors{CRGB{red, green, blue}} {}

    uint8_t &r() { return colors.r; }
    uint8_t &g() { return colors.g; }
    uint8_t &b() { return colors.b; }

    const uint8_t &r() const { return colors.r; }
    const uint8_t &g() const { return colors.g; }
    const uint8_t &b() const { return colors.b; }

    Lights::Color operator*(double scale) const
    {
      Color result;
      result.r() = static_cast<uint8_t>(std::clamp(r() * scale, 0.0, 255.0));
      result.g() = static_cast<uint8_t>(std::clamp(g() * scale, 0.0, 255.0));
      result.b() = static_cast<uint8_t>(std::clamp(b() * scale, 0.0, 255.0));
      return result;
    }

    Lights::Color operator*(uint8_t scale) const
    {
      Color result;
      result.r() = (r() * scale) / 255;
      result.g() = (g() * scale) / 255;
      result.b() = (b() * scale) / 255;
      return result;
    }

    Lights::Color operator/(double scale) const
    {
      Color result;
      result.r() = static_cast<uint8_t>(std::clamp(r() / scale, 0.0, 255.0));
      result.g() = static_cast<uint8_t>(std::clamp(g() / scale, 0.0, 255.0));
      result.b() = static_cast<uint8_t>(std::clamp(b() / scale, 0.0, 255.0));
      return result;
    }

    Lights::Color operator/(uint8_t scale) const
    {
      Color result;
      result.r() = (r() / scale) / 255;
      result.g() = (g() / scale) / 255;
      result.b() = (b() / scale) / 255;
      return result;
    }

    Lights::Color &operator*=(double scale)
    {
      r() = static_cast<uint8_t>(std::clamp(r() * scale, 0.0, 255.0));
      g() = static_cast<uint8_t>(std::clamp(g() * scale, 0.0, 255.0));
      b() = static_cast<uint8_t>(std::clamp(b() * scale, 0.0, 255.0));
      return *this;
    }

  private:
    CRGB colors;
  };
}