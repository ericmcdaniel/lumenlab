#include "lights/color2.h"

namespace Lights
{
  Color2 Color2::operator*(double scale) const
  {
    return Color2{
        static_cast<uint8_t>(std::clamp(r * scale, 0.0, 255.0)),
        static_cast<uint8_t>(std::clamp(g * scale, 0.0, 255.0)),
        static_cast<uint8_t>(std::clamp(b * scale, 0.0, 255.0))};
  }

  Color2 Color2::operator*(uint8_t scale) const
  {
    return Color2{
        static_cast<uint8_t>((r * scale) / 255),
        static_cast<uint8_t>((g * scale) / 255),
        static_cast<uint8_t>((b * scale) / 255)};
  }

  Color2 Color2::operator/(double scale) const
  {
    return Color2{
        static_cast<uint8_t>(std::clamp(r / scale, 0.0, 255.0)),
        static_cast<uint8_t>(std::clamp(g / scale, 0.0, 255.0)),
        static_cast<uint8_t>(std::clamp(b / scale, 0.0, 255.0))};
  }

  Color2 Color2::operator/(uint8_t scale) const
  {
    return Color2{
        static_cast<uint8_t>((r / scale) / 255),
        static_cast<uint8_t>((g / scale) / 255),
        static_cast<uint8_t>((b / scale) / 255)};
  }

  Color2 &Color2::operator*=(double scale)
  {
    r = static_cast<uint8_t>(std::clamp(r * scale, 0.0, 255.0));
    g = static_cast<uint8_t>(std::clamp(g * scale, 0.0, 255.0));
    b = static_cast<uint8_t>(std::clamp(b * scale, 0.0, 255.0));
    return *this;
  }
}