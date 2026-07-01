#pragma once

#include "platform/configuration.h"
#include "lights/color.h"
#include "lights/led-buffer.h"
#include "lights/led-luminance.h"
#include "engine/layer.h"

namespace Lights
{
  class LedStrip
  {
  public:
    LedStrip();

    LedBuffer buffer;
    Engine::Layer layer[SystemCore::Configuration::maxLeds];

    Color *getRawColors();
    static const uint16_t size() { return SystemCore::Configuration::numLeds(); }
    void reset();
    void adjustLuminance();

  private:
    LedLuminance luminance;
  };
}