#pragma once

#include "lights/color.h"

#include <cstdint>

namespace Engine
{
  struct RendererConfig
  {
    Lights::Color color;
    uint8_t alpha;
    uint16_t position;
  };
}