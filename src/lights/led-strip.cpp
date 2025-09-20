#include "lights/led-strip.h"

namespace Lights
{
  LedStrip::LedStrip(Engine::SystemConfig &configuration, Engine::RunState &state) : Time::Timeable{},
                                                                                     config{configuration},
                                                                                     size{configuration.numLeds},
                                                                                     buffer{configuration.numLeds},
                                                                                     luminance{configuration}
  {
    FastLED.addLeds<WS2815, 4>(static_cast<CRGB *>(buffer), size);
    Time::Timeable::wait(25000);
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

  void LedStrip::adjustLuminance()
  {
    luminance.adjustLuminance();
    for (int i = 0; i < size; ++i)
    {
      float scale = static_cast<float>(luminance.getLuminance()) / luminance.MAX_LED_BRIGHTNESS;
      buffer[i].r = static_cast<fl::u8>(buffer[i].r * scale);
      buffer[i].g = static_cast<fl::u8>(buffer[i].g * scale);
      buffer[i].b = static_cast<fl::u8>(buffer[i].b * scale);
    }
  }

  void LedStrip::updateColor()
  {
    if (isReady())
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