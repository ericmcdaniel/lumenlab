#include "engine/state-manager.h"
#include "logger.h"

namespace Engine
{
  void StateManager::setNext(StateOptions cs)
  {
    switch (cs)
    {
    case StateOptions::GameSandbox:
      if (curr != StateOptions::TransitionSandbox)
        curr = StateOptions::TransitionSandbox;
      else
        curr = cs;
      break;
    default:
      curr = cs;
      break;
    }
  };
}