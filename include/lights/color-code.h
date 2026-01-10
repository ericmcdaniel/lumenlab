#pragma once

#include <cstdint>

namespace Lights
{
  enum class ColorCode : uint32_t
  {
    MenuLightBlue = 0x4da6ff,
    MenuLightGreen = 0x4dff4d,
    GameBlue = 0x4da6ff,
    GameRed = 0xff4d4d,
    GameGreen = 0x4dff4d,
    GameYellow = 0xffd24d
  };
}