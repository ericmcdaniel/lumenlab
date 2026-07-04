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
    // for (const Lights::Pixel &pixel : model.getRendering())
    for (uint16_t i = 0; i < model.getRendering().size(); ++i)
    {
      const uint16_t pos = std::clamp(static_cast<uint16_t>(model.getPositionPrecise()), static_cast<uint16_t>(0), SystemCore::Configuration::numLeds());
      leds.buffer[pos + i] = model.getRendering()[i].color;
      leds.layer[pos + i] = model.getLayer();
      logf("Drawing position=%f, color=%u", model.getPositionPrecise() + i, model.getRendering()[i].alpha);
    }
    log(" ");
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