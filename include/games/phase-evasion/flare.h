#pragma once

#include "esp_system.h"

#include "common.h"

#include "engine/timer.h"
#include "engine/system-config.h"
#include "lights/color.h"
#include "lights/color-code.h"

namespace Games::PhaseEvasion
{
  class Flare : public Engine::Timer
  {
  public:
    Flare() = delete;
    Flare(const float s) : color{Lights::colorPalette[static_cast<uint16_t>(esp_random()) % arraySize(Lights::colorPalette)]},
                           positionFloat{Engine::SystemConfig::numLeds + width},
                           speed{s} {}
    static constexpr uint16_t width = 10;
    void updatePosition();
    uint16_t getPosition() const { return static_cast<uint16_t>(positionFloat); }
    const Lights::Color getColor() const { return color; }

  private:
    const Lights::Color color;
    const float speed;
    float positionFloat;
  };
}