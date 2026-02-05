#pragma once

#include <cstdint>

#include "core/configuration.h"

namespace Games::PhaseEvasion
{

  class Gem : public Engine::Timer
  {
  public:
    Gem() : active{false} { spawn(0); }

    static constexpr uint16_t width = 3;
    uint16_t getPosition() { return position; }
    bool isActive() { return active; }

    Lights::Color getColor() { return Lights::Color::NavajoWhite; }

    void capture() { active = false; }
    void spawn(const uint16_t pos)
    {
      bool isOutsideLeftRegion = pos < (width - 1);
      bool isOutsideRightRegion = pos > SystemCore::Configuration::numLeds + (width - 1);
      if (isOutsideLeftRegion || isOutsideRightRegion)
      {
        return;
      }

      position = pos;
      active = true;
    }

  private:
    uint16_t position;
    bool active;
  };
}