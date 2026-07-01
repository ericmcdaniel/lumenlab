#pragma once

#include "lights/led-strip.h"
// #include "engine/renderable.h"
#include "engine/pixel.h"
#include "engine/renderer-config.h"
#include "logger.h"

namespace Engine
{
  class Renderer
  {
  public:
    Renderer() = default;

    Lights::LedStrip leds;

    void drawPixel(const RendererConfig &config);

    template <uint16_t N>
    void renderEntity(const Pixels<N> &entity, uint16_t position, Layer layer)
    {
      for (const Pixel &ent : entity)
      {
        logf("Drawing...%x", ent.alpha);
      }
      log(" ");
    }

  private:
    void blend(const RendererConfig &config);
  };
}