#if !defined(USE_PS3)
#include <Bluepad32.h>
#include "player/ps4-controller.h"
#include "player/controller-properties.h"
#include "common.h"

namespace Player
{

  Ps4Controller *Ps4Controller::instance = nullptr;

  void Ps4Controller::begin()
  {
    BP32.setup(&onConnectedController, &onDisconnectedController);
  }

  const uint8_t Ps4Controller::rawButtonState(const ControllerButton button) const
  {
    if (!active || !active->isConnected())
      return 0;

    switch (button)
    {
    case ControllerButton::Cross:
      return instance->cross();
    case ControllerButton::Circle:
      return instance->circle();
    case ControllerButton::Square:
      return instance->square();
    case ControllerButton::Triangle:
      return instance->triangle();

    case ControllerButton::L1:
      return instance->l1();
    case ControllerButton::R1:
      return instance->r1();
    case ControllerButton::L2:
      return instance->l2();
    case ControllerButton::R2:
      return instance->r2();

    case ControllerButton::Up:
      return instance->up();
    case ControllerButton::Down:
      return instance->down();
    case ControllerButton::Left:
      return instance->left();
    case ControllerButton::Right:
      return instance->right();

    case ControllerButton::Ps:
      return instance->ps();
    case ControllerButton::Start:
      return instance->start();

    default:
      return 0;
    }
  }

  void Ps4Controller::poll()
  {
    BP32.update();
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

  void Ps4Controller::onConnectedController(ControllerPtr ctl)
  {
    if (instance)
      instance->onConnectedInternal(ctl);
  }

  void Ps4Controller::onDisconnectedController(ControllerPtr ctl)
  {
    if (instance)
      instance->onDisconnectedInternal(ctl);
  }

  void Ps4Controller::onConnectedInternal(ControllerPtr ctl)
  {
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++)
    {
      if (!controllers[i])
      {
        instance->controllers[i] = ctl;
        active = ctl;
        connection = true;
        break;
      }
    }
  }

  void Ps4Controller::onDisconnectedInternal(ControllerPtr ctl)
  {
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++)
    {
      if (controllers[i] == ctl)
      {
        controllers[i] = nullptr;
        if (active == ctl)
          active = nullptr;
        break;
      }
    }
  }

  const bool Ps4Controller::wasPressed(const ControllerButton button) const
  {
    return buttonPressedEvent[static_cast<int>(button)];
  }

  const bool Ps4Controller::wasPressedAndReleased(const ControllerButton button) const
  {
    return buttonReleasedEvent[static_cast<int>(button)];
  }

  bool Ps4Controller::isDown(const ControllerButton button) const
  {
    return rawButtonState(button);
  }

  uint8_t Ps4Controller::l2()
  {
    if (!controllers[0])
      return 0;

    return controllers[0]->brake();
  }

  uint8_t Ps4Controller::r2()
  {
    if (!controllers[0])
      return 0;

    return controllers[0]->throttle();
  }

  AnalogStick Ps4Controller::leftAnalog()
  {
    if (!active)
      return {0, 0};

    return {active->axisX(), active->axisY()};
  }

  AnalogStick Ps4Controller::rightAnalog()
  {
    if (!active)
      return {0, 0};

    return {active->axisRX(), active->axisRY()};
  }

  uint8_t Ps4Controller::button(uint16_t mask)
  {
    if (!controllers[0])
      return 0;

    return (controllers[0]->buttons() & mask) ? 255 : 0;
  }

  uint8_t Ps4Controller::dpad(uint16_t mask)
  {
    if (!controllers[0])
      return 0;

    return (controllers[0]->dpad() & mask) ? 255 : 0;
  }

  uint8_t Ps4Controller::misc(uint16_t mask)
  {
    if (!controllers[0])
      return 0;

    return (controllers[0]->miscSystem() & mask) ? 255 : 0;
  }
}
#endif