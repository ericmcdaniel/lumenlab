#pragma once

#include "esp_system.h"

#include "common.h"

#include "engine/timer.h"
#include "core/configuration.h"
#include "lights/color.h"

namespace Games::PhaseEvasion
{
  class Flare : public Engine::Timer
  {
  public:
    Flare() : active{false},
              color{Lights::Color::WhiteSmoke},
              speed{0.0f},
              positionFloat{SystemCore::Configuration::numLeds + width} {};

    static constexpr uint16_t width = 10;
    void updatePosition();
    uint16_t getPosition() const { return static_cast<uint16_t>(positionFloat); }

    const Lights::Color getColor() const { return color; }
    bool isActive() const { return active; }
    void activate(Lights::Color color, float speed);
    void deactivate();

  private:
    bool active;
    Lights::Color color;
    float speed;
    float positionFloat;
  };
}