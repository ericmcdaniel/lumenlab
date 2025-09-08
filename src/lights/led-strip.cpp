#include <FastLED.h>
#include "lights/led-strip.h"
#include "engine/engine.h"
#include "engine/timeable.h"
#include "engine/system-config.h"

namespace Lights
{
  LedStrip::LedStrip(Engine::SystemConfig &configuration, Engine::RunState &state) : Time::Timeable{state},
                                                                                     config{configuration},
                                                                                     size{configuration.numLeds}
  {
    leds = new CRGB[size];
    FastLED.addLeds<WS2815, 4>(leds, size);
  }
  void LedStrip::getColors() {}
}