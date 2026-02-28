#pragma once

#ifdef USE_PS3
#include <Ps3Controller.h>
#else
#include <Bluepad32.h>
#endif

namespace Player
{

  struct AnalogStick
  {
    int8_t x = 0;
    int8_t y = 0;
  };

  enum class ControllerButton : uint8_t
  {
    Cross,
    Circle,
    Triangle,
    Square,
    Up,
    Down,
    Left,
    Right,
    L1,
    L2,
    L3,
    R1,
    R2,
    R3,
    Start,
    Select,
    Ps
  };

  class Controller
  {
  public:
    Controller() { instance = this; }
    void begin(String macAddress);

#ifdef USE_PS3

    uint8_t cross() { return instance->controller.data.analog.button.cross; }
    uint8_t circle() { return instance->controller.data.analog.button.circle; }
    uint8_t triangle() { return instance->controller.data.analog.button.triangle; }
    uint8_t square() { return instance->controller.data.analog.button.square; }

    uint8_t l1() { return instance->controller.data.analog.button.l1; }
    uint8_t l2() { return instance->controller.data.analog.button.l2; }
    uint8_t r1() { return instance->controller.data.analog.button.r1; }
    uint8_t r2() { return instance->controller.data.analog.button.r2; }

    uint8_t up() { return instance->controller.data.analog.button.up; }
    uint8_t down() { return instance->controller.data.analog.button.down; }
    uint8_t left() { return instance->controller.data.analog.button.left; }
    uint8_t right() { return instance->controller.data.analog.button.right; }

    uint8_t start() { return instance->controller.data.button.start; }
    uint8_t ps() { return instance->controller.data.button.ps; }

#else
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

#endif

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
#ifdef USE_PS3
    Ps3Controller controller;
#else
    ::Controller controller;
#endif
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