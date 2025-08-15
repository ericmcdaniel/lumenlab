#pragma once

#include <FastLED.h>
#include "Timeable.h"

namespace Lights
{

  class LedStrip : protected Time::Timeable
  {
  private:
    unsigned int _size;
    CRGB leds[300];

  public:
    LedStrip(unsigned int size);
    void getColors();
  };
}