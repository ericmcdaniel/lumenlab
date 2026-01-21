#pragma once

#include "engine/timer.h"
#include "engine/system-config.h"
#include "lights/color.h"
#include "lights/color-code.h"

namespace Games
{
  class PhaseEvasionFlare : public Engine::Timer
  {
  public:
    PhaseEvasionFlare() = delete;
    PhaseEvasionFlare(const float s) : color{Lights::ColorCode::MenuLightBlue},
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