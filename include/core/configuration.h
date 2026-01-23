#pragma once

#include <cstdint>

namespace SystemCore
{
  struct Configuration
  {
    // REQUIRED: modify this address to match the mac address of your PS3 controller
    static constexpr char macAddress[] = "00:1b:fb:8e:87:ac";
    static constexpr uint16_t numLeds = 327;
    static constexpr uint32_t serialBaud = 921600;
    static constexpr uint16_t recallBoundaries[4] = {0, 113, 168, 281};
    static constexpr uint8_t ledDimmerGpio = 34;
  };
}