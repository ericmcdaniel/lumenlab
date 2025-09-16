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
    for (int i = 0; i < 300; i++)
    {
      leds[i].r = 255;
      leds[i].g = 255;
      leds[i].b = 255;
    }
    FastLED.addLeds<WS2815, 4>(leds, size);
    Time::Timeable::setTime(25000);
  }

  CRGB *LedStrip::getRawColors()
  {
    return leds;
  }

  void LedStrip::updateColor()
  {
    Serial.print("\n\nCurrent time: ");
    Serial.print(millis());
    Serial.print(", Next time: ");
    Serial.print(Time::Timeable::getNext());
    Serial.print("\nIs ready? ");
    if (Time::Timeable::isReady())
      Serial.print("Yes.\n");
    else
      Serial.print("No.\n");
    Serial.print("\n\n");
    if (Time::Timeable::isReady())
    {
      for (int i = 0; i < 300; i++)
      {
        leds[i].r = 255;
        leds[i].g = 0;
        leds[i].b = 36;
      }
    }
  }
}