#pragma once

#include "player/game-controller.h"
#include "engine/timeable.h"
#include "engine/system-config.h"

namespace Player
{
  class Player : public Time::Timeable
  {
  private:
    const Engine::SystemConfig &config;

  public:
    GameController controller;
    Player(Engine::SystemConfig &configuration, Engine::RunState &state) : Time::Timeable(state),
                                                                           config{configuration}
    {
      controller.begin(config.macAddress);
    };
  };
}