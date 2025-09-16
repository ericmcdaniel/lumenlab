#include "lights/led-strip.h"

namespace Lights
{
  LedStrip::LedStrip(Engine::SystemConfig &configuration, Engine::RunState &state) : Time::Timeable{state},
                                                                                     config{configuration},
                                                                                     size{configuration.numLeds},
                                                                                     buffer{configuration.numLeds}
  {
    FastLED.addLeds<WS2815, 4>(buffer.leds, size);
    Time::Timeable::setTime(25000);
  }

  CRGB *LedStrip::getRawColors()
  {
    return buffer.leds;
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
        buffer.leds[i].r = 255;
        buffer.leds[i].g = 0;
        buffer.leds[i].b = 36;
      }
    }
  }
}