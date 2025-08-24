#pragma once

#include <Ps3Controller.h>
#include "Exception.h"

namespace Player
{

  class Controller
  {
  public:
    Controller()
    {
      instance = this;
    }

    void begin()
    {
      // Ps3.attach(&Controller::staticCallback);
      instance->controller.begin("00:1b:fb:8e:87:ac");
      instance->controller.attachOnConnect(&Controller::onConnect);
    }

    // void getUpdate()
    // {
    //   Serial.println("\n\n");
    // }

    uint8_t cross() { return instance->controller.data.analog.button.cross; }
    uint8_t circle() { return instance->controller.data.analog.button.circle; }
    uint8_t triangle() { return instance->controller.data.analog.button.triangle; }
    uint8_t square() { return instance->controller.data.analog.button.square; }

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

    static Controller *instance;
    bool connection = false;
  };

  Controller *Controller::instance = nullptr;
}