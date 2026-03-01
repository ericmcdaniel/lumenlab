#ifndef USE_PS3

#pragma once

#include <Bluepad32.h>

#include "player/controller-properties.h"

namespace Player
{
  class Controller
  {
  public:
    Controller() { instance = this; }
    void begin(String macAddress);

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

    AnalogStick leftAnalog();
    AnalogStick rightAnalog();

    const uint8_t rawButtonState(const ControllerButton button) const;
    const bool wasPressed(const ControllerButton button) const;
    const bool wasPressedAndReleased(const ControllerButton button) const;
    const bool isConnected() const { return instance->connection; }
    void poll();
    bool isDown(const ControllerButton button) const;
    void reset();

  private:
    // ::Controller controller;
    uint32_t buttonDebouceEvent[17];
    static constexpr uint32_t buttonDebounceThreshold = 30;
    bool buttonLastState[17] = {0};
    bool buttonPressedEvent[17] = {0};
    bool buttonReleasedEvent[17] = {0};

    static Controller *instance;
    bool connection = false;
    uint32_t ignoreEventsUntil = 0;

    void handleOnConnect();
    int filterDeadZone(int8_t value, int deadZone = 3);
    static void onConnect()
    {
      if (instance)
        instance->handleOnConnect();
    }
  };
}

#endif