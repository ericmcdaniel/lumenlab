#if !defined(USE_PS3)

#pragma once

#include <Bluepad32.h>

#include "player/controller.h"
#include "player/controller-properties.h"

namespace Player
{
  class Ps4Controller : public Controller
  {
  public:
    Ps4Controller() : controller(nullptr) { instance = this; }
    void begin(String macAddress) {};

    uint8_t cross() { return 5; }    // instance->controller.data.button.cross; }
    uint8_t circle() { return 5; }   // instance->controller.data.button.circle; }
    uint8_t triangle() { return 5; } // instance->controller.data.button.triangle; }
    uint8_t square() { return 5; }   // instance->controller.data.button.square; }

    uint8_t l1() { return 5; } // instance->controller.data.button.l1; }
    uint8_t l2() { return 5; } // instance->controller.data.button.l2; }
    uint8_t r1() { return 5; } // instance->controller.data.button.r1; }
    uint8_t r2() { return 5; } // instance->controller.data.button.r2; }

    uint8_t up() { return 5; }    // instance->controller.data.button.up; }
    uint8_t down() { return 5; }  // instance->controller.data.button.down; }
    uint8_t left() { return 5; }  // instance->controller.data.button.left; }
    uint8_t right() { return 5; } // instance->controller.data.button.right; }

    uint8_t start() { return 5; }  // instance->controller.data.button.options; }
    uint8_t select() { return 5; } // instance->controller.data.button.share; }
    uint8_t ps() { return 5; }     // instance->controller.data.button.ps; }

    AnalogStick leftAnalog() { return {0, 0}; }
    AnalogStick rightAnalog() { return {0, 0}; }

    const uint8_t rawButtonState(const ControllerButton button) const override { return 0; }
    const bool wasPressed(const ControllerButton button) const override { return 0; }
    const bool wasPressedAndReleased(const ControllerButton button) const override { return 0; }
    const bool isConnected() const { return instance->connection; }
    void poll() {}
    bool isDown(const ControllerButton button) const { return false; }
    void reset() {}

  private:
    ::Controller *controller;

    static Ps4Controller *instance;
    bool connection = false;
    uint32_t ignoreEventsUntil = 0;
    void handleOnConnect() override {};
    static void onConnect()
    {
      if (instance)
        instance->handleOnConnect();
    }
  };
}

#endif