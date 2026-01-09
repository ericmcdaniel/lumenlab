#include <Arduino.h>

#include "lights/led-luminance.h"

namespace Lights
{
  void LedLuminance::adjustLuminance()
  {
    int dialReading = analogRead(config.ledDimmerGpio);
    dialReading = map(dialReading, 0, LedLuminance::MAX_ADC_READING, 0, LedLuminance::MAX_LED_BRIGHTNESS);
    dialReading = constrain(dialReading, 0, LedLuminance::MAX_LED_BRIGHTNESS);

    currentLuminance = dialReading;
  }

  uint8_t LedLuminance::applyGamma(uint8_t value)
  {
    constexpr float gamma = 2.2f;
    float normalized = value / 255.0f;
    return static_cast<uint8_t>(powf(normalized, gamma) * 255.0f + 0.5f);
  }
}