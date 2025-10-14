#pragma once

namespace Engine
{
  enum class RunState
  {
    MAIN_MENU,
    TRANSITION_SANDBOX,
    GAME_SANDBOX,
    NO_CONTROLLER_CONNECTION,
    ERROR
  };
}