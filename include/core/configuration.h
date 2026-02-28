#pragma once

#include <Arduino.h>
#include <Preferences.h>
#include <cstdint>

#ifndef LUMENLAB_VERSION
#define LUMENLAB_VERSION "v999.999.999"
#endif
#ifdef USE_PS3
#define PS_CONTROLLER_TYPE "PS3"
#else
#define PS_CONTROLLER_TYPE "PS4"
#endif

namespace SystemCore
{
  class Configuration
  {
  public:
    static const String &macAddress() { return _macAddress; }
    static uint16_t numLeds() { return _numLeds; }
    static uint32_t serialBaud() { return _serialBaud; }
    static const std::array<uint16_t, 3> &recallBoundaries() { return _recallBoundaries; }

    static constexpr char version[] = LUMENLAB_VERSION;
    static constexpr char psControllerType[] = PS_CONTROLLER_TYPE;
    static constexpr uint8_t ledDimmerGpio = 34; // set from PCB design, should not be configurable

    static void load(::Preferences &memory);

  private:
    static String _macAddress;
    static uint16_t _numLeds;
    static uint32_t _serialBaud;
    static std::array<uint16_t, 3> _recallBoundaries;
  };
}