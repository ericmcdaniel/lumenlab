#include "lights/led-strip.h"

namespace Lights
{
  LedStrip::LedStrip(Engine::SystemConfig &configuration) : config{configuration},
                                                            _size{config.numLeds},
                                                            buffer{config.numLeds},
                                                            luminance{configuration}
  {
#ifdef RELEASE
    FastLED.addLeds<WS2815, 4>(static_cast<Color *>(buffer), _size);
    reset();
#endif
  }

  Color *LedStrip::getRawColors()
  {
    return static_cast<Color *>(buffer);
  }

  void LedStrip::reset()
  {
    for (int i = 0; i < _size; i++)
    {
      buffer[i].colors.r = 0;
      buffer[i].colors.g = 0;
      buffer[i].colors.b = 0;
    }
  }

  void LedStrip::adjustLuminance()
  {
    luminance.adjustLuminance();
    for (int i = 0; i < _size; ++i)
    {
      float scale = static_cast<float>(luminance.getLuminance()) / LedLuminance::MAX_LED_BRIGHTNESS;
      buffer[i].colors.r = static_cast<fl::u8>(buffer[i].colors.r * scale);
      buffer[i].colors.g = static_cast<fl::u8>(buffer[i].colors.g * scale);
      buffer[i].colors.b = static_cast<fl::u8>(buffer[i].colors.b * scale);
    }
  }
}