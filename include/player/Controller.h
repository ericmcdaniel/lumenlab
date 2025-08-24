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
      controllerInstance = this;
    }

    void begin()
    {
      // Ps3.attach(&Controller::staticCallback);
      controllerInstance->controller.begin("00:1b:fb:8e:87:ac");
      controllerInstance->controller.attachOnConnect(&Controller::onConnect);
    }

    // void getUpdate()
    // {
    //   Serial.println("\n\n");
    // }

    uint8_t cross() { return controllerInstance->controller.data.analog.button.cross; }
    uint8_t circle() { return controllerInstance->controller.data.analog.button.circle; }
    uint8_t triangle() { return controllerInstance->controller.data.analog.button.triangle; }
    uint8_t square() { return controllerInstance->controller.data.analog.button.square; }

  private:
    Ps3Controller controller;

    static void onConnect()
    {
      if (controllerInstance)
      {
        controllerInstance->handleOnConnect();
      }
    }
    void handleOnConnect()
    {
      Serial.println("\n\nConnected.\n");
    }

    // static void staticCallback()
    // {
    //   if (controllerInstance)
    //   {
    //     controllerInstance->onEvent();
    //   }
    // }

    // void onEvent()
    // {
    //   if (Ps3.event.button_down.cross)
    //   {
    //     Serial.println("Cross pressed!");
    //   }
    // }

    static Controller *controllerInstance;
  };

  Controller *Controller::controllerInstance = nullptr;

  //   Controller()
  //   {
  //     // Ps3.attach(notify);

  //     Ps3.begin("00:1b:fb:8e:87:ac");
  //   }

}