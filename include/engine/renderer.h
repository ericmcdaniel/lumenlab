#pragma once

#include "lights/led-strip.h"
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

    void renderEntity(CustomDataStructures::Span<const Lights::Pixel> pixels, float positionPrecise, Layer layer)
    {
      for (const Lights::Pixel &pixel : pixels)
      {
        const uint16_t pos = static_cast<uint16_t>(std::clamp(positionPrecise, 0.0f, 300.0f));
        leds.buffer[pos] = pixel.color;
        leds.layer[pos] = layer;
        logf("Drawing Pos: %f", positionPrecise);
      }
      log(" ");
    }

  private:
    void blend(const RendererConfig &config);
  };
}