#pragma once

#include "engine/system-config.h"
#include "lights/color.h"
#include "lights/led-buffer.h"
#include "lights/led-luminance.h"

namespace Lights
{
  class LedStrip
  {
  public:
    LedBuffer buffer;
    LedStrip(Engine::SystemConfig &configuration);
    Color *getRawColors();

    static constexpr uint16_t size() { return Engine::SystemConfig::numLeds; }
    void reset();
    void adjustLuminance();

  private:
    const Engine::SystemConfig &config;
    LedLuminance luminance;
  };
}