#pragma once

#include "esp_system.h"

#include "common.h"

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
    PhaseEvasionFlare(const float s) : color{colorPalette[static_cast<uint16_t>(esp_random()) % arraySize(colorPalette)]},
                                       positionFloat{Engine::SystemConfig::numLeds + width},
                                       speed{s} {}
    static constexpr uint16_t width = 10;
    void updatePosition();
    uint16_t getPosition() const { return static_cast<uint16_t>(positionFloat); }
    const Lights::Color getColor() const { return color; }

  private:
    Lights::Color colorPalette[4] = {
        {Lights::ColorCode::GameBlue},    // ✕ blue
        {Lights::ColorCode::GameRed},     // ◯ red
        {Lights::ColorCode::GameGreen},   // △ green
        {Lights::ColorCode::GameYellow}}; // □ yellow

    const Lights::Color color;
    const float speed;
    float positionFloat;
  };
}