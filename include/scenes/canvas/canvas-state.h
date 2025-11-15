#pragma once

#include <cstdint>

namespace Scenes
{
  class CanvasSceneState
  {
  public:
    CanvasSceneState() : red{128}, green{128}, blue{128} {}
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    void reset() { red = green = blue = 128; }
  };
}