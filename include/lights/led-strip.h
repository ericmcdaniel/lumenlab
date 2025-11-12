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

    constexpr uint16_t size() const { return _size; }
    void reset();
    void adjustLuminance();

  private:
    const Engine::SystemConfig &config;
    uint16_t _size;
    LedLuminance luminance;
  };
}