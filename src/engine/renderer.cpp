#include <algorithm>
#include "engine/renderer.h"

namespace Engine
{
  Renderer::Renderer()
  {
  }

  void Renderer::drawPixel(const RendererConfig &config)
  {
    if (config.color.layer < leds2.buffer[config.position].layer)
      return;

    if (config.alpha == 0)
      return;

    if (config.alpha == 255)
    {
      leds2.buffer[config.position] = config.color;
      return;
    }
    blend(config);
  }

  void Renderer::blend(const RendererConfig &config)
  {
    Lights::Color2 led = leds2.buffer[config.position];
    led.r = std::clamp((led.r * (255 - config.alpha) + (config.color.r * config.alpha)) / 255, 0, 255);
    led.g = std::clamp((led.g * (255 - config.alpha) + (config.color.g * config.alpha)) / 255, 0, 255);
    led.b = std::clamp((led.b * (255 - config.alpha) + (config.color.b * config.alpha)) / 255, 0, 255);
    led.layer = config.color.layer;
  }
}