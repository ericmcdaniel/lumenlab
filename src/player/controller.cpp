#include <stdlib.h>
#include <cmath>
#include "player/controller.h"
#include "logger.h"
#include "common.h"

#ifdef USE_PS3
#include <Ps3Controller.h>
#else
#include <Bluepad32.h>
#endif

namespace Player
{
  // Following Singleton pattern. Only one instance of the game controller can exist
  Controller *Controller::instance = nullptr;

  void Controller::begin(String macAddress)
  {
#ifdef USE_PS3
    instance->controller.begin(macAddress.c_str());
    instance->controller.attachOnConnect(&Controller::onConnect);
#endif
  }

  AnalogStick Controller::leftAnalog()
  {
#ifdef USE_PS3
    AnalogStick joystick;
    auto &analog = instance->controller.data.analog.stick;

    joystick.x = filterDeadZone(analog.lx);
    joystick.y = filterDeadZone(analog.ly);

    return joystick;
#else
    return {0, 0};
#endif
  }

  AnalogStick Controller::rightAnalog()
  {
#ifdef USE_PS3
    AnalogStick joystick;
    auto &analog = instance->controller.data.analog.stick;

    joystick.x = filterDeadZone(analog.rx);
    joystick.y = filterDeadZone(analog.ry);

    return joystick;
#else
    return {0, 0};
#endif
  }

  const uint8_t Controller::rawButtonState(const ControllerButton button) const
  {
    if (!instance->connection)
      return 0;

#ifdef USE_PS3
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
#else
    switch (button)
    {
    case ControllerButton::Cross:
      return 0; // instance->controller.data.button.cross;
    case ControllerButton::Circle:
      return 0; // instance->controller.data.button.circle;
    case ControllerButton::Triangle:
      return 0; // instance->controller.data.button.triangle;
    case ControllerButton::Square:
      return 0; // instance->controller.data.button.square;
    case ControllerButton::Up:
      return 0; // instance->controller.data.button.up;
    case ControllerButton::Down:
      return 0; // instance->controller.data.button.down;
    case ControllerButton::Left:
      return 0; // instance->controller.data.button.left;
    case ControllerButton::Right:
      return 0; // instance->controller.data.button.right;
    case ControllerButton::L1:
      return 0; // instance->controller.data.button.l1;
    case ControllerButton::L2:
      return 0; // instance->controller.data.button.l2;
    case ControllerButton::L3:
      return 0; // instance->controller.data.button.l3;
    case ControllerButton::R1:
      return 0; // instance->controller.data.button.r1;
    case ControllerButton::R2:
      return 0; // instance->controller.data.button.r2;
    case ControllerButton::R3:
      return 0; // instance->controller.data.button.r3;
    case ControllerButton::Start:
      return 0; // instance->controller.data.button.options;
    case ControllerButton::Select:
      return 0; // instance->controller.data.button.share;
    case ControllerButton::Ps:
      return 0; // instance->controller.data.button.ps;
    default:
      return 0;
    }
#endif
  }

  const bool Controller::wasPressed(const ControllerButton button) const
  {
    uint32_t idx = static_cast<uint32_t>(button);
    return instance->buttonPressedEvent[idx];
  }

  const bool Controller::wasPressedAndReleased(const ControllerButton button) const
  {
    uint32_t idx = static_cast<uint32_t>(button);
    return instance->buttonReleasedEvent[idx];
  }

  bool Controller::isDown(const ControllerButton button) const
  {
    uint32_t idx = static_cast<uint32_t>(button);
    return instance->buttonLastState[idx];
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

    if (millis() < ignoreEventsUntil)
    {
      for (uint32_t i = 0; i < arraySize(buttonLastState); ++i)
      {
        auto btn = static_cast<ControllerButton>(i);
        bool raw = rawButtonState(btn) != 0;
        buttonLastState[i] = raw;
        buttonDebouceEvent[i] = millis();
      }
      return;
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
    instance->connection = true;
    instance->ignoreEventsUntil = millis() + 200;
    instance->reset();
    instance->poll();
  }

  int Controller::filterDeadZone(int8_t value, int deadZone)
  {
    if (std::abs(value) <= deadZone)
      return 0;

    constexpr float responseExponent = 1.5f;
    const int8_t maxRaw = 127;

    float sign = (value > 0) ? 1.0f : -1.0f;
    float magnitude = static_cast<float>(std::abs(value) - deadZone);
    float normalizedAnalogValue = magnitude / static_cast<float>(maxRaw - deadZone);
    normalizedAnalogValue = std::clamp(normalizedAnalogValue, 0.0f, 1.0f);

    float scaled = std::pow(normalizedAnalogValue, responseExponent);
    int output = static_cast<int>(std::round(scaled * static_cast<float>(maxRaw)));
    return static_cast<int>(sign * output);
  }
}