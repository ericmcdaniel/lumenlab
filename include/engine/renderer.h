#pragma once

#include "lights/led-strip.h"
#include "engine/renderer-config.h"

namespace Engine
{
  class Renderer
  {
  public:
    Renderer();

    Lights::LedStrip leds;

    void drawPixel(const RendererConfig &config);

  private:
    void blend(const RendererConfig &config);
  };
}