#pragma once

#include <Arduino.h>
#include <Preferences.h>
#include <cstdint>

namespace SystemCore
{
  class Configuration
  {
  public:
    static const String &version() { return _version; }
    static const String &macAddress() { return _macAddress; }
    static uint16_t numLeds() { return _numLeds; }
    static uint32_t serialBaud() { return _serialBaud; }
    static const std::array<uint16_t, 4> &recallBoundaries() { return _recallBoundaries; }
    static constexpr uint8_t ledDimmerGpio = 34; // set from PCB design

    static void load(::Preferences &memory);

  private:
    static String _version;
    static String _macAddress;
    static uint16_t _numLeds;
    static uint32_t _serialBaud;
    static std::array<uint16_t, 4> _recallBoundaries;
  };
}