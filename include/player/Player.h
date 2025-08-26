#pragma once

#include "player/controller.h"
#include "engine/system-config.h"

namespace Player
{
  class Player
  {

  public:
    Controller controller;
    Player(const Engine::SystemConfig &config)
    {
      controller.begin(config.macAddress);
    };
  };
}