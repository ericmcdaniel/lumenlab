#pragma once

#include "player/controller.h"
#include "engine/system-config.h"

namespace Player
{
  class Player
  {
  private:
    const Engine::SystemConfig &config;

  public:
    Controller controller;
    Player(Engine::SystemConfig &configuration) : config{configuration}
    {
      controller.begin(config.macAddress);
    };
  };
}