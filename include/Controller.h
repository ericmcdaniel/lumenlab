#pragma once

#include <Ps3Controller.h>

class Controller
{
private:
  ps3_t _data;

public:
  void update_state();

  uint8_t cross() { return _data.analog.button.cross; }
  uint8_t circle() { return _data.analog.button.circle; }
  uint8_t triangle() { return _data.analog.button.triangle; }
  uint8_t square() { return _data.analog.button.square; }
};