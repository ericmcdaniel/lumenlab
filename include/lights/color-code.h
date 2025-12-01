#pragma once

#include <cstdint>

namespace Lights
{
  enum class ColorCode : uint32_t
  {
    MenuLightBlue = 0x4DA6ff,
    MenuLightGreen = 0x4DFF4D,
    GameBlue = 0x4DA6FF,
    GameRed = 0xFF4D4D,
    GameGreen = 0x4DFF4D,
    GameYellow = 0xFFD24D
  };
}