#pragma once

#include "secrets.h"

namespace Engine
{
  struct SystemConfig
  {
    static constexpr const unsigned int numLeds{NUM_LEDS};
    static constexpr const char *macAddress{MAC_ADDRESS};
    static constexpr const unsigned int serialBaud{SERIAL_BAUD};
  };
}