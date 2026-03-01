#pragma once

#include <cstdint>
#include <Arduino.h>

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
    virtual ~Controller() = default;
    virtual void begin(String macAddress) = 0;

    virtual uint8_t cross() = 0;
    virtual uint8_t circle() = 0;
    virtual uint8_t triangle() = 0;
    virtual uint8_t square() = 0;

    virtual uint8_t l1() = 0;
    virtual uint8_t l2() = 0;
    virtual uint8_t r1() = 0;
    virtual uint8_t r2() = 0;

    virtual uint8_t up() = 0;
    virtual uint8_t down() = 0;
    virtual uint8_t left() = 0;
    virtual uint8_t right() = 0;

    virtual uint8_t start() = 0;
    virtual uint8_t ps() = 0;

    virtual AnalogStick leftAnalog() = 0;
    virtual AnalogStick rightAnalog() = 0;

    virtual const uint8_t rawButtonState(const ControllerButton button) const = 0;
    virtual const bool wasPressed(const ControllerButton button) const = 0;
    virtual const bool wasPressedAndReleased(const ControllerButton button) const = 0;
    virtual const bool isConnected() const = 0;
    virtual void poll() = 0;
    virtual bool isDown(const ControllerButton button) const = 0;
    void reset();

  protected:
    uint32_t buttonDebouceEvent[17];
    static constexpr uint32_t buttonDebounceThreshold = 30;
    bool buttonLastState[17] = {0};
    bool buttonPressedEvent[17] = {0};
    bool buttonReleasedEvent[17] = {0};

    bool connection = false;
    uint32_t ignoreEventsUntil = 0;

    virtual void handleOnConnect() = 0;
    int filterDeadZone(int8_t value, int deadZone = 3);
  };
}