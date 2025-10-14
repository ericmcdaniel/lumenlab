#pragma once

#include "engine/timer.h"
#include "engine/run-state.h"
#include "player/controller.h"

namespace Engine
{

  class Navigation : Engine::Timer
  {
  private:
    Engine::RunState state;
    Player::Controller controller;

  public:
    Navigation(Engine::RunState &_state, const Player::Controller &_controller) : state(_state), controller(_controller) {};
    void handleNavigationChange();
  };
}