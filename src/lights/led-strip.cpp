#include <FastLED.h>
#include "lights/led-strip.h"
#include "system-config.h"

namespace Lights
{
  LedStrip::LedStrip(const SystemConfig &config) : _size(config.numLeds)
  {
    leds = new CRGB[_size];
    FastLED.addLeds<WS2815, 4>(leds, _size);
  }
  void LedStrip::getColors() {}
}