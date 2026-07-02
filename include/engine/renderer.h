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
    void renderEntity(const Pixels<N> &pixels, float position, Layer l)
    {
      for (const Pixel &pixel : pixels)
      {
        const uint16_t pos = static_cast<uint16_t>(std::clamp(position, 0.0f, 300.0f));
        leds[pos] = pixel.color;
        leds.layer[pos] = pixel.layer;
        logf("Drawing Pos: %u", position);
      }
      log(" ");
    }

  private:
    void blend(const RendererConfig &config);
  };
}