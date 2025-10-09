#pragma once

#include "engine/timeable.h"
#include "engine/run-state.h"
#include "player/game-controller.h"

namespace Engine
{

  class Navigation : Time::Timeable
  {
  private:
    Engine::RunState state;
    Player::GameController controller;

  public:
    Navigation(Engine::RunState &_state, const Player::GameController &_controller) : state(_state), controller(_controller) {};
    void handleNavigationChange();
  };
}