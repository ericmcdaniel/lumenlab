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

    Color &operator[](uint16_t index) { return buffer[index]; }
    const Color &operator[](uint16_t index) const { return buffer[index]; }

    Color *getRawColors();
    static const uint16_t size() { return SystemCore::Configuration::numLeds(); }
    void reset();
    void adjustLuminance();

  protected:
    Engine::Layer layer[SystemCore::Configuration::maxLeds];

  private:
    LedLuminance luminance;
  };
}