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
    Flare() = default;

    static constexpr uint16_t width = 10;
    void updatePosition();
    uint16_t getPosition() const { return static_cast<uint16_t>(positionFloat); }

    const Lights::Color getColor() const { return color; }
    bool isActive() const { return active; }
    void activate(Lights::Color color, float speed);
    void deactivate();
    bool completedCycle = false;

  private:
    bool active = false;
    Lights::Color color = Lights::Color::WhiteSmoke;
    float speed = 0.0f;
    float positionFloat = SystemCore::Configuration::numLeds + width;
  };
}