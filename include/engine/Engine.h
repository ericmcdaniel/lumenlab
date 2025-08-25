#pragma once

namespace Engine
{
  enum class State
  {
    STARTUP,
    GAME,
    INVALID
  };

  class Engine
  {
  public:
    State currentAction;

    Engine() : currentAction(State::STARTUP) {}
  };
}