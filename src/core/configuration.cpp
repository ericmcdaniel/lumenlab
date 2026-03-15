#include "core/configuration.h"
#include <Preferences.h>

#ifndef LUMENLAB_VERSION
#define LUMENLAB_VERSION "v99.99.99"
#endif
#ifdef USE_PS3
#define PS_CONTROLLER_TYPE "PS3"
#else
#define PS_CONTROLLER_TYPE "PS4"
#endif

namespace SystemCore
{
  String Configuration::_version;
  String Configuration::_psControllerType;
  String Configuration::_macAddress;
  uint16_t Configuration::_numLeds;
  uint32_t Configuration::_serialBaud;
  std::array<uint16_t, 3> Configuration::_recallBoundaries;

  void Configuration::load(::Preferences &memory)
  {
    _version = LUMENLAB_VERSION;
    _psControllerType = PS_CONTROLLER_TYPE;
    _macAddress = memory.getString("macAddress", "00:00:00:00:00:00");
    _numLeds = static_cast<uint16_t>(memory.getString("numLeds", "300").toInt());
    _serialBaud = static_cast<uint32_t>(memory.getString("serialBaud", "921600").toInt());

    _recallBoundaries[0] = static_cast<uint16_t>(memory.getString("boundary_1", "75").toInt());
    _recallBoundaries[1] = static_cast<uint16_t>(memory.getString("boundary_2", "150").toInt());
    _recallBoundaries[2] = static_cast<uint16_t>(memory.getString("boundary_3", "225").toInt());
  }
}