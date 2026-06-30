#pragma once

#include "lights/color2.h"

#include <cstdint>

namespace Engine
{
  struct RendererConfig
  {
    Lights::Color2 color;
    uint8_t alpha;
    uint16_t position;
  };
}