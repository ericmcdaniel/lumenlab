#pragma once

#include <cstdint>

#include "lights/color.h"

namespace Scenes
{
  class CanvasSceneState
  {
  public:
    CanvasSceneState() : currentColor{} {}
    Lights::Color currentColor;
  };
}