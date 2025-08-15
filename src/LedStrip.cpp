#include <FastLED.h>
#include "LedStrip.h"

namespace Lights
{
  LedStrip::LedStrip(unsigned int size) : _size(size)
  {
    FastLED.addLeds<WS2815, 4, RGB>(leds, _size);
  }
  void LedStrip::getColors() {}
}