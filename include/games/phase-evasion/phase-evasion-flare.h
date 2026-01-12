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
                                                   position{ctx->config.numLeds + width} {}

    static constexpr uint16_t width = 10;
    void updatePosition();
    uint16_t getPosition() { return position; }

  private:
    Core::ContextManager *contextManager;
    Lights::ColorCode color;
    uint16_t position;
  };
}