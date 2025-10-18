#pragma once

namespace Engine
{
  struct SystemConfig
  {
    // REQUIRED: modify this address to match the mac address of your PS3 controller
    static constexpr const char *macAddress = "00:1b:fb:8e:87:ac";

    static constexpr const unsigned int numLeds = 300;
    static constexpr const unsigned int serialBaud = 921600;
    static constexpr const unsigned short ledDimmerGpio = 34;
  };
}