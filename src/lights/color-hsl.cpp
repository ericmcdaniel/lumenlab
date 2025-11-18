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
    double red = r / 255.0;
    double green = g / 255.0;
    double blue = b / 255.0;

    double maxChannel = std::max({red, green, blue});
    double minChannel = std::min({red, green, blue});
    double channelDelta = maxChannel - minChannel;

    double lightness = (maxChannel + minChannel) * 0.5;
    double hue = 0.0;
    double saturation = 0.0;

    if (channelDelta > 0.00001)
    {
      if (lightness < 0.5)
        saturation = channelDelta / (maxChannel + minChannel);
      else
        saturation = channelDelta / (2.0 - maxChannel - minChannel);

      if (maxChannel == red)
        hue = fmodf(((green - blue) / channelDelta), 6.0);
      else if (maxChannel == green)
        hue = ((blue - red) / channelDelta) + 2.0;
      else
        hue = ((red - green) / channelDelta) + 4.0;

      hue *= 60.0;
      if (hue < 0.0)
        hue += 360.0;
    }

    uint8_t hueByte = static_cast<uint8_t>((hue / 360.0) * 255.0 + 0.5);
    uint8_t saturationByte = static_cast<uint8_t>(saturation * 255.0 + 0.5);
    uint8_t lightnessByte = static_cast<uint8_t>(lightness * 255.0 + 0.5);

    return ColorHsl(hueByte, saturationByte, lightnessByte);
  }

  Color ColorHsl::toColor() const
  {
    double hue = (hslValues.h / 255.0) * 360.0;
    double saturation = hslValues.s / 255.0;
    double lightness = hslValues.v / 255.0;

    double chroma = (1.0 - std::fabs(2.0 * lightness - 1.0)) * saturation;
    double hueSection = hue / 60.0;
    double secondary = chroma * (1.0 - std::fabs(fmodf(hueSection, 2.0) - 1.0));

    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;

    if (0.0 <= hueSection && hueSection < 1.0)
    {
      red = chroma;
      green = secondary;
    }
    else if (1.0 <= hueSection && hueSection < 2.0)
    {
      red = secondary;
      green = chroma;
    }
    else if (2.0 <= hueSection && hueSection < 3.0)
    {
      green = chroma;
      blue = secondary;
    }
    else if (3.0 <= hueSection && hueSection < 4.0)
    {
      green = secondary;
      blue = chroma;
    }
    else if (4.0 <= hueSection && hueSection < 5.0)
    {
      red = secondary;
      blue = chroma;
    }
    else if (5.0 <= hueSection && hueSection < 6.0)
    {
      red = chroma;
      blue = secondary;
    }

    double matchValue = lightness - chroma * 0.5;

    uint8_t redByte = static_cast<uint8_t>((red + matchValue) * 255.0 + 0.5);
    uint8_t greenByte = static_cast<uint8_t>((green + matchValue) * 255.0 + 0.5);
    uint8_t blueByte = static_cast<uint8_t>((blue + matchValue) * 255.0 + 0.5);

    return Color(redByte, greenByte, blueByte);
  }
}
