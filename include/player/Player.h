#pragma once

#include "player/controller.h"
#include "system-config.h"

namespace Player
{
  class Player
  {

  public:
    Controller controller;
    Player(const SystemConfig &config)
    {
      controller.begin(config.macAddress);
    };
  };
}