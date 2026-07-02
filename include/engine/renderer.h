#pragma once

#include "lights/led-strip.h"
#include "lights/pixel.h"
#include "engine/render-model.h"
#include "logger.h"
#include <span.h>

namespace Engine
{
  class Renderer
  {
  public:
    Renderer() = default;

    Lights::LedStrip leds;

    void drawPixel(const RenderModel &model);
    void renderEntity(const RenderModel &model);

  private:
    void blend(const RenderModel &model);
  };
}