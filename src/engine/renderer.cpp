#include <algorithm>
#include "engine/renderer.h"
#include "logger.h"

namespace Engine
{
  void Renderer::drawPixel(const RenderModel &renderModel, const uint16_t normalizedPosition, uint16_t offset)
  {
    if (renderModel.getLayer() < leds.layer[normalizedPosition + offset])
      return;

    const Lights::Pixel pixel = renderModel.getRendering()[offset];

    if (pixel.alpha == 0)
      return;

    if (pixel.alpha == 255)
    {
      leds.buffer[normalizedPosition + offset] = pixel.color;
      return;
    }

    // blend(model);
  }

  void Renderer::renderEntity(const RenderModel &renderModel)
  {
    CustomDataStructures::Span<const Lights::Pixel> model = renderModel.getRendering();
    for (uint16_t offset = 0; offset < model.size(); ++offset)
    {
      const uint16_t roundedPosition = static_cast<uint16_t>(renderModel.getPositionPrecise());
      const uint16_t normalizedPosition = std::clamp(roundedPosition, static_cast<uint16_t>(0), SystemCore::Configuration::numLeds());
      drawPixel(renderModel, normalizedPosition, offset);
      leds.layer[normalizedPosition + offset] = renderModel.getLayer();
    }
  }

  void Renderer::blend(const RenderModel &config)
  {
    // Lights::Color led = leds.buffer[config.position];
    // led.r = std::clamp((led.r * (255 - config.alpha) + (config.color.r * config.alpha)) / 255, 0, 255);
    // led.g = std::clamp((led.g * (255 - config.alpha) + (config.color.g * config.alpha)) / 255, 0, 255);
    // led.b = std::clamp((led.b * (255 - config.alpha) + (config.color.b * config.alpha)) / 255, 0, 255);
    // led.layer = config.color.layer;
  }
}