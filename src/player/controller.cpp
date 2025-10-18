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

  const uint8_t Controller::buttonState(const ControllerButton button) const
  {
    switch (button)
    {
    case ControllerButton::Cross:
      return instance->controller.data.analog.button.cross;
    case ControllerButton::Circle:
      return instance->controller.data.analog.button.circle;
    case ControllerButton::Triangle:
      return instance->controller.data.analog.button.triangle;
    case ControllerButton::Square:
      return instance->controller.data.analog.button.square;
    case ControllerButton::Up:
      return instance->controller.data.analog.button.up;
    case ControllerButton::Down:
      return instance->controller.data.analog.button.down;
    case ControllerButton::Left:
      return instance->controller.data.analog.button.left;
    case ControllerButton::Right:
      return instance->controller.data.analog.button.right;
    case ControllerButton::L1:
      return instance->controller.data.analog.button.l1;
    case ControllerButton::L2:
      return instance->controller.data.analog.button.l2;
    case ControllerButton::L3:
      return instance->controller.data.button.l3;
    case ControllerButton::R1:
      return instance->controller.data.analog.button.r1;
    case ControllerButton::R2:
      return instance->controller.data.analog.button.r2;
    case ControllerButton::R3:
      return instance->controller.data.button.r3;
    case ControllerButton::Start:
      return instance->controller.data.button.start;
    case ControllerButton::Select:
      return instance->controller.data.button.select;
    case ControllerButton::Ps:
      return instance->controller.data.button.ps;
    default:
      return false;
    }
  }

  const bool Controller::wasPressed(ControllerButton button)
  {
    uint32_t mask = 1u << static_cast<uint8_t>(button);
    bool isDownNow = buttonState(button);
    bool wasDownBefore = (buttonsPressed & mask);

    if (isDownNow && !wasDownBefore)
    {
      buttonsPressed |= mask;
      return true;
    }

    if (!isDownNow)
    {
      buttonsPressed &= ~mask;
    }

    return false;
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