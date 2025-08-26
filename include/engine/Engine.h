#pragma once

namespace Engine
{
  enum class RunState
  {
    STARTUP,
    GAME,
    INVALID
  };

  class GameEngine
  {
  public:
    RunState currentAction;

    GameEngine() : currentAction(RunState::STARTUP) {}
  };
}