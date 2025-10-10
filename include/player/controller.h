#pragma once

#include <Ps3Controller.h>

#include "logger.h"

namespace Player
{

  struct AnalogStick
  {
    int8_t x = 0;
    int8_t y = 0;
  };

  class Controller
  {
  public:
    Controller() { instance = this; }
    void begin(const char *macAddress);

    uint8_t cross() { return instance->controller.data.analog.button.cross; }
    uint8_t circle() { return instance->controller.data.analog.button.circle; }
    uint8_t triangle() { return instance->controller.data.analog.button.triangle; }
    uint8_t square() { return instance->controller.data.analog.button.square; }

    uint8_t up() { return instance->controller.data.analog.button.up; }
    uint8_t down() { return instance->controller.data.analog.button.down; }
    uint8_t left() { return instance->controller.data.analog.button.left; }
    uint8_t right() { return instance->controller.data.analog.button.right; }

    uint8_t start() { return instance->controller.data.button.start; }
    uint8_t ps() { return instance->controller.data.button.ps; }

    AnalogStick leftAnalog();
    AnalogStick rightAnalog();

    const bool isConnected() { return instance->connection; }

  private:
    Ps3Controller controller;

    static void onConnect();
    void handleOnConnect();
    int filterDeadZone(int8_t value, int deadZone = 3);
    static Controller *instance;
    bool connection = false;
  };
}