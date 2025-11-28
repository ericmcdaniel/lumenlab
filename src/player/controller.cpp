#include <stdlib.h>
#include <Ps3Controller.h>
#include "player/controller.h"
#include "logger.h"
#include "common.h"

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

  const uint8_t Controller::rawButtonState(const ControllerButton button) const
  {
    if (!instance->connection)
      return 0;

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
      return 0;
    }
  }

  const bool Controller::wasPressed(const ControllerButton button)
  {
    uint32_t idx = static_cast<uint32_t>(button);
    return instance->buttonPressedEvent[idx];
  }

  const bool Controller::wasPressedAndReleased(const ControllerButton button)
  {
    uint32_t idx = static_cast<uint32_t>(button);
    return instance->buttonReleasedEvent[idx];
  }

  void Controller::reset()
  {
    for (uint32_t i = 0; i < arraySize(buttonPressedEvent); ++i)
    {
      buttonPressedEvent[i] = false;
      buttonReleasedEvent[i] = false;
      buttonLastState[i] = rawButtonState(static_cast<ControllerButton>(i));
      buttonDebouceEvent[i] = 0;
    }
  }

  void Controller::poll()
  {
    for (uint32_t i = 0; i < arraySize(buttonPressedEvent); ++i)
    {
      buttonPressedEvent[i] = false;
      buttonReleasedEvent[i] = false;
    }

    for (uint32_t i = 0; i < arraySize(buttonLastState); ++i)
    {
      auto btn = static_cast<ControllerButton>(i);
      bool raw = rawButtonState(btn) != 0;

      uint32_t now = millis();
      if (raw && !buttonLastState[i])
      {
        if (now - buttonDebouceEvent[i] > buttonDebounceThreshold)
        {
          buttonPressedEvent[i] = true;
          buttonLastState[i] = true;
          buttonDebouceEvent[i] = now;
        }
      }
      else if (!raw && buttonLastState[i])
      {
        if (now - buttonDebouceEvent[i] > buttonDebounceThreshold)
        {
          buttonReleasedEvent[i] = true;
          buttonLastState[i] = false;
          buttonDebouceEvent[i] = now;
        }
      }
    }
  }

  void Controller::handleOnConnect()
  {
    log("Game controller connected successfully.");
    instance->reset();
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