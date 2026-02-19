#pragma once

#include <Arduino.h>
#include <Preferences.h>
#include <cstdint>

namespace SystemCore
{
  class Configuration
  {
  public:
    static const String &version() { return version_; }
    static const String &macAddress() { return macAddress_; }
    static uint16_t numLeds() { return numLeds_; }
    static uint32_t serialBaud() { return serialBaud_; }

    static void load(class Preferences &memory)
    {
      version_ = memory.getString("version", "v0.0.0");
      macAddress_ = memory.getString("macAddress", "00:1b:fb:8e:87:ac");
      numLeds_ = memory.getUInt("numLeds", 327);
      serialBaud_ = memory.getUInt("serialBaud", 921600);
    }

    // (in progress)
    static constexpr uint16_t recallBoundaries[4] = {0, 113, 168, 281};
    static constexpr uint8_t ledDimmerGpio = 34;

  private:
    static String version_;
    static String macAddress_;
    static uint16_t numLeds_;
    static uint32_t serialBaud_;
  };
}