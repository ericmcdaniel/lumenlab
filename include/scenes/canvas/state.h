#pragma once

#include <cstdint>

#include "lights/color.h"

namespace Scenes::Canvas
{
  class SceneState
  {
  public:
    SceneState() : currentColor{} {}
    Lights::Color currentColor;
  };
}