#pragma once

#include "platform/configuration.h"
#include "lights/color2.h"
#include "lights/led-buffer2.h"
#include "lights/led-luminance.h"

namespace Lights
{
  class LedStrip2
  {
  public:
    LedStrip2();
    LedBuffer2 buffer;
    Color2 *getRawColors();

    static const uint16_t size() { return SystemCore::Configuration::numLeds(); }
    void reset();
    void adjustLuminance();

  private:
    LedLuminance luminance;
  };
}