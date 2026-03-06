#ifdef USE_PS3
#pragma once

#include <Ps3Controller.h>
#include "player/controller.h"

namespace Player
{

  class Ps3Controller : public Controller
  {
  public:
    Ps3Controller() : controller(&Ps3) { instance = this; }

    void begin(String macAddress);
    uint8_t cross() override { return instance->controller->data.analog.button.cross; }
    uint8_t circle() override { return instance->controller->data.analog.button.circle; }
    uint8_t triangle() override { return instance->controller->data.analog.button.triangle; }
    uint8_t square() override { return instance->controller->data.analog.button.square; }

    uint8_t l1() override { return instance->controller->data.analog.button.l1; }
    uint8_t l2() override { return instance->controller->data.analog.button.l2; }
    uint8_t r1() override { return instance->controller->data.analog.button.r1; }
    uint8_t r2() override { return instance->controller->data.analog.button.r2; }

    uint8_t up() override { return instance->controller->data.analog.button.up; }
    uint8_t down() override { return instance->controller->data.analog.button.down; }
    uint8_t left() override { return instance->controller->data.analog.button.left; }
    uint8_t right() override { return instance->controller->data.analog.button.right; }

    uint8_t start() override { return instance->controller->data.button.start; }
    uint8_t ps() override { return instance->controller->data.button.ps; }

    AnalogStick leftAnalog() override;
    AnalogStick rightAnalog() override;

    const uint8_t rawButtonState(const ControllerButton button) const;
    const bool wasPressed(const ControllerButton button) const;
    const bool wasPressedAndReleased(const ControllerButton button) const;
    const bool isConnected() const { return instance->connection; }
    void poll();
    bool isDown(const ControllerButton button) const;

  private:
    ::Ps3Controller *controller;
    static Ps3Controller *instance;

    void handleOnConnect();
    static void onConnect()
    {
      if (instance)
        instance->handleOnConnect();
    }
  };
}
#endif