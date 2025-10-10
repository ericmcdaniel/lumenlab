#include <stdlib.h>
#include <Ps3Controller.h>
#include "player/controller.h"
#include "logger.h"

namespace Player
{
  // Following Singleton pattern. Only one instance of the game controller can exist
  Controller *Controller::instance = nullptr;

  void Controller::begin(const char *macAddress)
  {
    instance->controller.begin(macAddress);
    instance->controller.attachOnConnect(&Controller::onConnect);
  }

  AnalogStick Controller::leftAnalog()
  {
    AnalogStick joystick;
    auto &analog = instance->controller.data.analog.stick;

    joystick.x = filterDeadZone(analog.lx);
    joystick.y = filterDeadZone(analog.ly);

    return joystick;
  }

  AnalogStick Controller::rightAnalog()
  {
    AnalogStick joystick;
    auto &analog = instance->controller.data.analog.stick;

    joystick.x = filterDeadZone(analog.rx);
    joystick.y = filterDeadZone(analog.ry);

    return joystick;
  }

  void Controller::onConnect()
  {
    if (instance)
    {
      instance->handleOnConnect();
    }
  }

  void Controller::handleOnConnect()
  {
    log("Game controller connected successfully.");
    instance->connection = true;
  }

  int Controller::filterDeadZone(int8_t value, int deadZone)
  {
    // This filters out the a dead zone, which is something my PS3 controller
    // suffers from. When you release any of the analog sticks, it rarely returns
    // precisely to the coordinate origin 0/0, but is always off by a few. This
    // changes every time you move the joystick around and return it, making
    // calibration efforts useless.
    if (abs(value) < deadZone)
      return 0;
    return (value > 0) ? value - deadZone : value + deadZone;
  };
}