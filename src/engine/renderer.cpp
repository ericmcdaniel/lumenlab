#include <algorithm>
#include "engine/renderer.h"
#include "logger.h"

namespace Engine
{
  void Renderer::drawPixel(const RenderModel &model)
  {
    // // if (model.color.layer < leds.buffer[model.position].layer)
    // // return;

    // if (model.alpha == 0)
    //   return;

    // if (model.alpha == 255)
    // {
    //   leds.buffer[model.position] = model.color;
    //   return;
    // }
    // blend(model);
  }

  void Renderer::renderEntity(const RenderModel &model)
  {
    for (uint16_t offset = 0; offset < model.getRendering().size(); ++offset)
    {
      const uint16_t roundedPosition = static_cast<uint16_t>(model.getPositionPrecise());
      const uint16_t normalizedPosition = std::clamp(roundedPosition, static_cast<uint16_t>(0), SystemCore::Configuration::numLeds());
      leds.buffer[normalizedPosition + offset] = model.getRendering()[offset].color;
      leds.layer[normalizedPosition + offset] = model.getLayer();
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