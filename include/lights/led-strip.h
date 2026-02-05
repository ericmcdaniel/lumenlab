#pragma once

#include "core/configuration.h"
#include "lights/color.h"
#include "lights/led-buffer.h"
#include "lights/led-luminance.h"

namespace Lights
{
  class LedStrip
  {
  public:
    LedStrip();
    LedBuffer buffer;
    Color *getRawColors();

    static constexpr uint16_t size() { return SystemCore::Configuration::numLeds; }
    void reset();
    void adjustLuminance();

  private:
    LedLuminance luminance;
  };
}