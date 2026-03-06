#if !defined(USE_PS3)
#pragma once

#include <Bluepad32.h>
#include "player/controller.h"

namespace Player
{

  class Ps4Controller : public Controller
  {
  public:
    Ps4Controller() { instance = this; };

    void begin(String macAddress);
    void poll() override;

    uint8_t cross() override { return button(0x1); }
    uint8_t circle() override { return button(0x2); }
    uint8_t square() override { return button(0x4); }
    uint8_t triangle() override { return button(0x8); }

    uint8_t l1() { return button(0x10); }
    uint8_t r1() { return button(0x20); }
    uint8_t l2() override;
    uint8_t r2() override;

    uint8_t up() override { return dpad(0x1); }
    uint8_t down() override { return dpad(0x2); }
    uint8_t right() override { return dpad(0x4); }
    uint8_t left() override { return dpad(0x8); }

    uint8_t ps() override { return misc(0x1); }
    uint8_t start() override { return misc(0x4); }

    AnalogStick leftAnalog() override;
    AnalogStick rightAnalog() override;

    const uint8_t rawButtonState(const ControllerButton button) const override;
    const bool wasPressed(const ControllerButton button) const override;
    const bool wasPressedAndReleased(const ControllerButton button) const override;
    const bool isConnected() const override { return connection; }
    bool isDown(const ControllerButton button) const override;

  private:
    ControllerPtr controllers[BP32_MAX_GAMEPADS] = {nullptr};
    ControllerPtr active = nullptr;

    void onConnectedInternal(ControllerPtr ctl);
    void onDisconnectedInternal(ControllerPtr ctl);

    static void onConnectedController(ControllerPtr ctl);
    static void onDisconnectedController(ControllerPtr ctl);
    uint8_t button(uint16_t mask);
    uint8_t dpad(uint16_t mask);
    uint8_t misc(uint16_t mask);

    static Ps4Controller *instance;
  };

}
#endif