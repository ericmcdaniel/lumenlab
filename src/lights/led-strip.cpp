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

    constexpr float redGain = 1.0f;
    constexpr float greenGain = 0.65f;
    constexpr float blueGain = 0.45f;

    float brightnessScale = static_cast<float>(luminance.getLuminance()) / LedLuminance::MAX_LED_BRIGHTNESS;

    for (uint16_t i = 0; i < size(); ++i)
    {
      Color &c = buffer[i];

      float r = c.r * brightnessScale;
      float g = c.g * brightnessScale;
      float b = c.b * brightnessScale;

      r *= redGain;
      g *= greenGain;
      b *= blueGain;

      r = std::clamp(r, 0.0f, 255.0f);
      g = std::clamp(g, 0.0f, 255.0f);
      b = std::clamp(b, 0.0f, 255.0f);

      c.r = LedLuminance::applyGamma(static_cast<uint8_t>(r));
      c.g = LedLuminance::applyGamma(static_cast<uint8_t>(g));
      c.b = LedLuminance::applyGamma(static_cast<uint8_t>(b));
    }
  }
}