#include "lights/led-strip.h"

namespace Lights
{
  LedStrip::LedStrip(Engine::SystemConfig &configuration) : config{configuration},
                                                            buffer{configuration.numLeds},
                                                            luminance{configuration}
  {
#ifdef RELEASE
    FastLED.addLeds<WS2815, 4>(static_cast<Color *>(buffer), size());
    reset();
#endif
  }

  Color *LedStrip::getRawColors()
  {
    return static_cast<Color *>(buffer);
  }

  void LedStrip::reset()
  {
    for (int i = 0; i < size(); i++)
    {
      buffer[i] = 0;
    }
  }

  void LedStrip::adjustLuminance()
  {
    luminance.adjustLuminance();
    for (int i = 0; i < size(); ++i)
    {
      float scale = static_cast<float>(luminance.getLuminance()) / LedLuminance::MAX_LED_BRIGHTNESS;
      buffer[i] = buffer[i] * scale;
    }
  }
}