#include <cmath>
#include <algorithm>
#include "lights/color-hsl.h"

namespace Lights
{

  ColorHsl::ColorHsl() : hslValues{0, 0, 0} {}
  ColorHsl::ColorHsl(uint8_t hue, uint8_t saturation, uint8_t lightness)
      : hslValues{hue, saturation, lightness} {}

  uint8_t &ColorHsl::hue() { return hslValues.h; }
  uint8_t &ColorHsl::saturation() { return hslValues.s; }
  uint8_t &ColorHsl::lightness() { return hslValues.v; }

  const uint8_t &ColorHsl::hue() const { return hslValues.h; }
  const uint8_t &ColorHsl::saturation() const { return hslValues.s; }
  const uint8_t &ColorHsl::lightness() const { return hslValues.v; }

  ColorHsl ColorHsl::fromRGB(uint8_t r, uint8_t g, uint8_t b)
  {
    float red = r / 255.0f;
    float green = g / 255.0f;
    float blue = b / 255.0f;

    float maxChannel = std::max({red, green, blue});
    float minChannel = std::min({red, green, blue});
    float channelDelta = maxChannel - minChannel;

    float lightness = (maxChannel + minChannel) * 0.5f;
    float hue = 0.0f;
    float saturation = 0.0f;

    if (channelDelta > 0.00001f)
    {
      if (lightness < 0.5f)
        saturation = channelDelta / (maxChannel + minChannel);
      else
        saturation = channelDelta / (2.0f - maxChannel - minChannel);

      if (maxChannel == red)
        hue = fmodf(((green - blue) / channelDelta), 6.0f);
      else if (maxChannel == green)
        hue = ((blue - red) / channelDelta) + 2.0f;
      else
        hue = ((red - green) / channelDelta) + 4.0f;

      hue *= 60.0f;
      if (hue < 0.0f)
        hue += 360.0f;
    }

    uint8_t hueByte = static_cast<uint8_t>((hue / 360.0f) * 255.0f + 0.5f);
    uint8_t saturationByte = static_cast<uint8_t>(saturation * 255.0f + 0.5f);
    uint8_t lightnessByte = static_cast<uint8_t>(lightness * 255.0f + 0.5f);

    return ColorHsl(hueByte, saturationByte, lightnessByte);
  }

  Color ColorHsl::toColor() const
  {
    float hue = (hslValues.h / 255.0f) * 360.0f;
    float saturation = hslValues.s / 255.0f;
    float lightness = hslValues.v / 255.0f;

    float chroma = (1.0f - std::fabs(2.0f * lightness - 1.0f)) * saturation;
    float hueSection = hue / 60.0f;
    float secondary = chroma * (1.0f - std::fabs(fmodf(hueSection, 2.0f) - 1.0f));

    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;

    if (0.0f <= hueSection && hueSection < 1.0f)
    {
      red = chroma;
      green = secondary;
    }
    else if (1.0f <= hueSection && hueSection < 2.0f)
    {
      red = secondary;
      green = chroma;
    }
    else if (2.0f <= hueSection && hueSection < 3.0f)
    {
      green = chroma;
      blue = secondary;
    }
    else if (3.0f <= hueSection && hueSection < 4.0f)
    {
      green = secondary;
      blue = chroma;
    }
    else if (4.0f <= hueSection && hueSection < 5.0f)
    {
      red = secondary;
      blue = chroma;
    }
    else if (5.0f <= hueSection && hueSection < 6.0f)
    {
      red = chroma;
      blue = secondary;
    }

    float matchValue = lightness - chroma * 0.5f;

    uint8_t redByte = static_cast<uint8_t>((red + matchValue) * 255.0f + 0.5f);
    uint8_t greenByte = static_cast<uint8_t>((green + matchValue) * 255.0f + 0.5f);
    uint8_t blueByte = static_cast<uint8_t>((blue + matchValue) * 255.0f + 0.5f);

    return Color(redByte, greenByte, blueByte);
  }

}
