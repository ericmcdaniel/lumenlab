#pragma once

// #include "platform/context-manager.h"
#include "lights/led-strip.h"
#include "lights/led-strip2.h"

namespace Engine
{
  class Renderer
  {
  public:
    Renderer();

    Lights::LedStrip leds;
    Lights::LedStrip2 leds2;

  private:
    // SystemCore::ContextManager contextManager;
    // uint32_t lastRender = 0;
  };
}