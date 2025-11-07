#pragma once

#include <cstdint>

namespace Engine
{
  struct SystemConfig
  {
    // REQUIRED: modify this address to match the mac address of your PS3 controller
    static constexpr const char *macAddress = "00:1b:fb:8e:87:ac";
    static constexpr const uint16_t numLeds = 300;
    static constexpr const uint32_t serialBaud = 921600;
    static constexpr const uint16_t recallBoundaries[4] = {0, 112, 150, 262};
    static constexpr const unsigned short ledDimmerGpio = 34;
  };
}