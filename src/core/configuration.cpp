#include "core/configuration.h"
#include <Preferences.h>

namespace SystemCore
{
  String Configuration::_version;
  String Configuration::_macAddress;
  uint16_t Configuration::_numLeds;
  uint32_t Configuration::_serialBaud;
  std::array<uint16_t, 4> Configuration::_recallBoundaries;

  void Configuration::load(::Preferences &memory)
  {
    _version = memory.getString("version", "v0.0.0");
    _macAddress = memory.getString("macAddress", "00:1b:fb:8e:87:ac");
    _numLeds = memory.getUInt("numLeds", 327);
    _serialBaud = memory.getUInt("serialBaud", 921600);

    _recallBoundaries[0] = memory.getUInt("boundary-0", 0);
    _recallBoundaries[1] = memory.getUInt("boundary-1", 113);
    _recallBoundaries[2] = memory.getUInt("boundary-2", 168);
    _recallBoundaries[3] = memory.getUInt("boundary-3", 281);
  }
}