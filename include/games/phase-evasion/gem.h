#pragma once

#include <cstdint>

#include "core/configuration.h"

namespace Games::PhaseEvasion
{

  class Gem
  {
  public:
    Gem() { reset(0); }

    static constexpr uint16_t width = 3;
    uint16_t getPosition() { return position; }

    void capture() { isCaptured = true; }
    void reset(const uint16_t pos)
    {
      bool isOutsideLeftRegion = pos < (width - 1);
      bool isOutsideRightRegion = pos > SystemCore::Configuration::numLeds;
      if (isOutsideLeftRegion || isOutsideRightRegion)
      {
        return;
      }

      position = pos;
      isCaptured = false;
    }

  private:
    uint16_t position;
    bool isCaptured;
  };
}