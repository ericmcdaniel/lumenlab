#pragma once

#include <Ps3Controller.h>

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
    void begin(const char *macAddress);

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

    AnalogStick leftAnalog();
    AnalogStick rightAnalog();

    const uint8_t rawButtonState(const ControllerButton button) const;
    const bool wasPressed(const ControllerButton button) const;
    const bool wasPressedAndReleased(const ControllerButton button) const;
    const bool isConnected() const { return instance->connection; }
    void poll();
    bool isDown(const ControllerButton button) const;
    void reset();
    float analogToSpeed(int value, float maxOutput) const;
    void setResponseExponent(float exp) { responseExponent = exp; }
    void setResponseBlend(float blend) { responseBlend = blend; }

  private:
    Ps3Controller controller;
    uint32_t buttonDebouceEvent[17];
    static constexpr uint32_t buttonDebounceThreshold = 30;
    bool buttonLastState[17] = {0};
    bool buttonPressedEvent[17] = {0};
    bool buttonReleasedEvent[17] = {0};
    float responseExponent = 2.0f;
    float responseBlend = 0.35f;
    static Controller *instance;
    bool connection = false;

    void handleOnConnect();
    int filterDeadZone(int8_t value, int deadZone = 3);
    static void onConnect()
    {
      if (instance)
        instance->handleOnConnect();
    }
  };
}