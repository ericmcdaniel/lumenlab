#ifdef USE_PS3

#include <stdlib.h>
#include <cmath>
#include "player/ps3-controller.h"
#include "logger.h"
#include "common.h"

#include <Ps3Controller.h>

namespace Player
{
  // Following Singleton pattern. Only one instance of the game controller can exist
  Ps3Controller *Ps3Controller::instance = nullptr;

  void Ps3Controller::begin(String macAddress)
  {
    instance->controller->begin(macAddress.c_str());
    instance->controller->attachOnConnect(&Ps3Controller::onConnect);
  }

  AnalogStick Ps3Controller::leftAnalog()
  {
    AnalogStick joystick;
    auto &analog = instance->controller->data.analog.stick;

    joystick.x = filterDeadZone(analog.lx);
    joystick.y = filterDeadZone(analog.ly);

    return joystick;
  }

  AnalogStick Ps3Controller::rightAnalog()
  {
    AnalogStick joystick;
    auto &analog = instance->controller->data.analog.stick;

    joystick.x = filterDeadZone(analog.rx);
    joystick.y = filterDeadZone(analog.ry);

    return joystick;
  }

  void Ps3Controller::rumble(RumbleOptions option)
  {
    switch (option)
    {
    case RumbleOptions::DoublePulse:
      break;
    default:
      break;
    }
  }

  const uint8_t Ps3Controller::rawButtonState(const ControllerButton button) const
  {
    if (!instance->connection)
      return 0;

    switch (button)
    {
    case ControllerButton::Cross:
      return instance->controller->data.analog.button.cross;
    case ControllerButton::Circle:
      return instance->controller->data.analog.button.circle;
    case ControllerButton::Triangle:
      return instance->controller->data.analog.button.triangle;
    case ControllerButton::Square:
      return instance->controller->data.analog.button.square;
    case ControllerButton::Up:
      return instance->controller->data.analog.button.up;
    case ControllerButton::Down:
      return instance->controller->data.analog.button.down;
    case ControllerButton::Left:
      return instance->controller->data.analog.button.left;
    case ControllerButton::Right:
      return instance->controller->data.analog.button.right;
    case ControllerButton::L1:
      return instance->controller->data.analog.button.l1;
    case ControllerButton::L2:
      return instance->controller->data.analog.button.l2;
    case ControllerButton::L3:
      return instance->controller->data.button.l3;
    case ControllerButton::R1:
      return instance->controller->data.analog.button.r1;
    case ControllerButton::R2:
      return instance->controller->data.analog.button.r2;
    case ControllerButton::R3:
      return instance->controller->data.button.r3;
    case ControllerButton::Start:
      return instance->controller->data.button.start;
    case ControllerButton::Select:
      return instance->controller->data.button.select;
    case ControllerButton::Ps:
      return instance->controller->data.button.ps;
    default:
      return 0;
    }
  }

  const bool Ps3Controller::wasPressed(const ControllerButton button) const
  {
    uint32_t idx = static_cast<uint32_t>(button);
    return instance->buttonPressedEvent[idx];
  }

  const bool Ps3Controller::wasPressedAndReleased(const ControllerButton button) const
  {
    uint32_t idx = static_cast<uint32_t>(button);
    return instance->buttonReleasedEvent[idx];
  }

  bool Ps3Controller::isDown(const ControllerButton button) const
  {
    uint32_t idx = static_cast<uint32_t>(button);
    return instance->buttonLastState[idx];
  }

  void Ps3Controller::poll()
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

  void Ps3Controller::handleOnConnect()
  {
    log("Game controller connected successfully.");
    instance->connection = true;
    instance->ignoreEventsUntil = millis() + 200;
    instance->reset();
    instance->poll();
  }

  void Ps3Controller::playRumblePattern(RumbleStep *pattern, int steps)
  {
    for (int i = 0; i < steps; i++)
    {
      Ps3.setRumble(pattern[i].intensity, pattern[i].duration);
      delay(pattern[i].duration);
    }
  }

  void Ps3Controller::rumbleTask(void *pvParameters)
  {
    RumbleStep *pattern = (RumbleStep *)pvParameters;
    int steps = 4; // example

    playRumblePattern(pattern, steps);

    vTaskDelete(NULL);
  }

  void Ps3Controller::triggerRumble(RumbleStep *pattern)
  {
    xTaskCreatePinnedToCore(
        Ps3Controller::rumbleTask,
        "RumbleTask",
        2048,
        (void *)pattern,
        1,
        NULL,
        0);
  }
}
#endif