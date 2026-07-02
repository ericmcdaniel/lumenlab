#pragma once

#include "lights/led-strip.h"
// #include "engine/renderable.h"
#include "lights/pixel.h"
#include "engine/renderer-config.h"
#include "logger.h"
#include <span.h>

namespace Engine
{
  class Renderer
  {
  public:
    Renderer() = default;

    Lights::LedStrip leds;

    void drawPixel(const RendererConfig &config);

    void renderEntity(CustomDataStructures::Span<const Lights::Pixel> pixels, float position, Layer l)
    {
      for (const Lights::Pixel &pixel : pixels)
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