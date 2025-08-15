#pragma once

#include <Ps3Controller.h>

class Controller
{
private:
  ps3_t _data;

public:
  void update_state();

  uint8_t cross() { return _data.analog.button.cross; }
};