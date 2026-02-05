#pragma once

#include "core/configuration.h"

namespace Lights
{
  class LedLuminance
  {
  public:
    LedLuminance() {}

    static constexpr float MAX_LED_BRIGHTNESS = 255.0f;
    static constexpr int MAX_ADC_READING = 4095;

    int getLuminance() { return currentLuminance; }
    void adjustLuminance();
    static uint8_t applyGamma(uint8_t value);

  private:
    int currentLuminance = MAX_ADC_READING;
  };
}