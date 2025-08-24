#pragma once

#include <Ps3Controller.h>
#include "player/Controller.h"
#include "Exception.h"

namespace Player
{
  class Player
  {
    // private:

  public:
    Controller controller;
    Player() : controller()
    {
      controller.begin();
    };
  };
}