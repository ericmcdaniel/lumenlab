#pragma once

#include <FastLED.h>
#include "timeable.h"
#include "system-config.h"

namespace Lights
{

  class LedStrip : protected Time::Timeable
  {
  private:
    unsigned int _size;
    CRGB *leds;

  public:
    LedStrip(const SystemConfig &config);
    void getColors();
  };
}