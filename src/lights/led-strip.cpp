#include "lights/led-strip.h"

namespace Lights
{
  LedStrip::LedStrip(Engine::SystemConfig &configuration, Engine::RunState &state) : Time::Timeable{state},
                                                                                     config{configuration},
                                                                                     size{configuration.numLeds},
                                                                                     buffer{configuration.numLeds}
  {
    FastLED.addLeds<WS2815, 4>(static_cast<CRGB *>(buffer), size);
    Time::Timeable::setTime(25000);
    setDefault();
  }

  CRGB *LedStrip::getRawColors()
  {
    return static_cast<CRGB *>(buffer);
  }

  void LedStrip::setDefault()
  {
    for (int i = 0; i < size; i++)
    {
      buffer[i].r = 128;
      buffer[i].g = 128;
      buffer[i].b = 128;
    }
  }

  void LedStrip::updateColor()
  {
    if (Time::Timeable::isReady())
    {
      for (int i = 0; i < size; i++)
      {
        buffer[i].r = 255;
        buffer[i].g = 0;
        buffer[i].b = 36;
      }
    }
  }
}