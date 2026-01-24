#pragma once

#include "esp_system.h"

#include "common.h"

#include "engine/timer.h"
#include "core/configuration.h"
#include "lights/color.h"
#include "lights/color-code.h"

namespace Games::PhaseEvasion
{
  class Flare : public Engine::Timer
  {
  public:
    Flare() : active{false},
              color{Lights::ColorCode::GameRed},
              speed{0.75},
              positionFloat{SystemCore::Configuration::numLeds + width} {};

    Flare(const float s) : color{Lights::colorPalette[static_cast<uint16_t>(esp_random()) % arraySize(Lights::colorPalette)]},
                           positionFloat{SystemCore::Configuration::numLeds + width},
                           speed{s} {}
    static constexpr uint16_t width = 10;
    void updatePosition();
    uint16_t getPosition() const { return static_cast<uint16_t>(positionFloat); }

    const Lights::Color getColor() const { return color; }
    const bool isActive() const { return active; }
    void activate();
    void deactivate();

  private:
    bool active = false;
    const Lights::Color color;
    const float speed;
    float positionFloat;
  };
}