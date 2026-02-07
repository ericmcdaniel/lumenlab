#pragma once

#include <cstdint>

namespace Lights
{
  enum class ColorCode : uint32_t
  {
    ThemeBlue = 0x4da6ff,
    ThemeRed = 0xff4d4d,
    ThemeGreen = 0x4dff4d,
    ThemeYellow = 0xffd24d,
    MenuUnselected = 0x5a5a50,
  };
}