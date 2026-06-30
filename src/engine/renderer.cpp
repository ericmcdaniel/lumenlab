#include "engine/renderer.h"

namespace Engine
{
  Renderer::Renderer()
  {
  }

  void Renderer::drawPixel(const RendererConfig &config)
  {
    // if config.layer < led2[position].layer -> pass
    // if config.layer >= led2[position].layer, then:
    //      if alpha == 255, Overwrite with config rgb
    //      else if alpha == 0, pass
    //      else: Blend the colors.
    if (config.color.layer < leds2.buffer[config.position].layer)
      return;

    if (config.alpha == 0)
      return;

    if (config.alpha == 0xff)
    {
      leds2.buffer[config.position] = config.color;
      return;
    }

    // blend
  }
}