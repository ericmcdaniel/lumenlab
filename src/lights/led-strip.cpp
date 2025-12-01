#include "lights/led-strip.h"

namespace Lights
{
  LedStrip::LedStrip(Engine::SystemConfig &configuration) : config{configuration},
                                                            buffer{configuration.numLeds},
                                                            luminance{configuration}
  {
#ifdef RELEASE
    FastLED.addLeds<WS2815, 18, GRB>(static_cast<Color *>(buffer), size());
    // FastLED.setCorrection(0xFFB0F0);
    // FastLED.setTemperature(0xFFE0A0);
    reset();
#endif
  }

  Color *LedStrip::getRawColors()
  {
    return static_cast<Color *>(buffer);
  }

  void LedStrip::reset()
  {
    for (uint16_t i = 0; i < size(); i++)
    {
      buffer[i] = 0;
    }
  }

  void LedStrip::adjustLuminance()
  {
    luminance.adjustLuminance();
    for (uint16_t i = 0; i < size(); ++i)
    {
      float scale = static_cast<float>(luminance.getLuminance()) / LedLuminance::MAX_LED_BRIGHTNESS;
      buffer[i] = buffer[i] * scale;
    }
  }
}