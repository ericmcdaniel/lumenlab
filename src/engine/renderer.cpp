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
      leds.layer[normalizedPosition + offset] = renderModel.getLayer();
      return;
    }

    blend(renderModel, normalizedPosition, offset);
  }

  void Renderer::renderEntity(const RenderModel &renderModel)
  {
    CustomDataStructures::Span<const Lights::Pixel> model = renderModel.getRendering();
    for (uint16_t offset = 0; offset < model.size(); ++offset)
    {
      const uint16_t roundedPosition = static_cast<uint16_t>(renderModel.getPositionPrecise());
      const uint16_t normalizedPosition = std::clamp(roundedPosition, static_cast<uint16_t>(0), static_cast<uint16_t>(SystemCore::Configuration::numLeds() - 1));
      drawPixel(renderModel, normalizedPosition, offset);
    }
  }

  void Renderer::blend(const RenderModel &renderModel, const uint16_t normalizedPosition, uint16_t offset)
  {
    Lights::Color &destLed = leds.buffer[normalizedPosition + offset];
    const auto &pixel = renderModel.getRendering()[offset];

    const uint16_t alpha = pixel.alpha;
    const uint16_t inverseAlpha = 255 - alpha;

    destLed.r = (destLed.r * inverseAlpha + pixel.color.r * alpha) / 255;
    destLed.g = (destLed.g * inverseAlpha + pixel.color.g * alpha) / 255;
    destLed.b = (destLed.b * inverseAlpha + pixel.color.b * alpha) / 255;
  }
}