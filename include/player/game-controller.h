#pragma once

#include <Ps3Controller.h>

namespace Player
{

  enum class AnalogStickSide
  {
    Left,
    Right
  };

  template <AnalogStickSide side>
  struct AnalogStick
  {
    uint8_t x = 0;
    uint8_t y = 0;
  };

  class GameController
  {
  public:
    GameController()
    {
      instance = this;
    }

    void begin(const char *macAddress);

    uint8_t cross() { return instance->controller.data.analog.button.cross; }
    uint8_t circle() { return instance->controller.data.analog.button.circle; }
    uint8_t triangle() { return instance->controller.data.analog.button.triangle; }
    uint8_t square() { return instance->controller.data.analog.button.square; }

    AnalogStick<AnalogStickSide::Left> leftAnalog()
    {
      AnalogStick<AnalogStickSide::Left> stick;
      stick.x = instance->controller.data.analog.stick.lx;
      stick.y = instance->controller.data.analog.stick.ly;
      return stick;
    }

    AnalogStick<AnalogStickSide::Right> rightAnalog()
    {
      AnalogStick<AnalogStickSide::Right> stick;
      stick.x = instance->controller.data.analog.stick.rx;
      stick.y = instance->controller.data.analog.stick.ry;
      return stick;
    }

    const bool isConnected() { return instance->connection; }

  private:
    Ps3Controller controller;

    static void onConnect()
    {
      if (instance)
      {
        instance->handleOnConnect();
      }
    }
    void handleOnConnect()
    {
      Serial.println("\n\nConnected.\n");
      instance->connection = true;
    }

    // static void staticCallback()
    // {
    //   if (instance)
    //   {
    //     instance->onEvent();
    //   }
    // }

    // void onEvent()
    // {
    //   if (Ps3.event.button_down.cross)
    //   {
    //     Serial.println("Cross pressed!");
    //   }
    // }

    static GameController *instance;
    bool connection = false;
  };
}