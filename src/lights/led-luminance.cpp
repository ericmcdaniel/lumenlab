#include <Arduino.h>

#include "lights/led-luminance.h"

namespace Lights
{
  void LedLuminance::adjustLuminance()
  {
    int dialReading = analogRead(config.ledDimmerGpio);
    dialReading = map(dialReading, 0, MAX_ADC_READING, 0, MAX_LED_BRIGHTNESS);
    dialReading = constrain(dialReading, 0, MAX_LED_BRIGHTNESS);

    currentLuminance = dialReading;
  }
}