#include <FastLED.h>
#include "lights/LedStrip.h"

namespace Lights
{
  LedStrip::LedStrip(unsigned int size) : _size(size)
  {
    leds = new CRGB[_size];
    FastLED.addLeds<WS2815, 4>(leds, _size);
  }
  void LedStrip::getColors() {}
}