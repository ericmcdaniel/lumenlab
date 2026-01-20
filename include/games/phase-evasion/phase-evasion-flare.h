#pragma once

#include "engine/timer.h"
#include "core/context-manager.h"
#include "lights/color-code.h"

namespace Games
{
  class PhaseEvasionFlare : public Engine::Timer
  {
  public:
    PhaseEvasionFlare(Core::ContextManager *ctx) : contextManager{ctx},
                                                   color{Lights::ColorCode::MenuLightBlue},
                                                   positionFloat{ctx->config.numLeds + width},
                                                   speed{0.75f} {}
    static constexpr uint16_t width = 10;
    void updatePosition();
    uint16_t getPosition() const { return static_cast<uint16_t>(positionFloat); }
    Lights::Color getColor() { return color; }

  private:
    const Core::ContextManager *contextManager;
    const Lights::Color color;
    float positionFloat;
    float speed;
  };
}