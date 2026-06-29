#pragma once

// #include "platform/context-manager.h"
#include "lights/led-strip.h"

namespace Engine
{
  class Renderer
  {
  public:
    Renderer();

    Lights::LedStrip leds;

  private:
    // SystemCore::ContextManager contextManager;
    // uint32_t lastRender = 0;
  };
}