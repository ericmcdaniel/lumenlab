#pragma once

#include "lights/color.h"
#include "engine/layer.h"

namespace Lights
{
  struct Pixel
  {
    Color color;
    uint8_t alpha = 0xff;
  };
}