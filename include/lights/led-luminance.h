#pragma once

#include "engine/system-config.h"

namespace Lights
{
  class LedLuminance
  {
  public:
    LedLuminance(Engine::SystemConfig &configuration) : config{configuration} {}

    static constexpr float MAX_LED_BRIGHTNESS = 255.0f;
    static constexpr int MAX_ADC_READING = 4095;

    int getLuminance() { return currentLuminance; }
    void adjustLuminance();

  private:
    const Engine::SystemConfig &config;
    int currentLuminance = MAX_ADC_READING;
  };
}