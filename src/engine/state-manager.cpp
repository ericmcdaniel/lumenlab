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
      {
        log("Transitioning to Game (Sandbox) (Transition Layer).");
        curr = StateOptions::TransitionSandbox;
      }
      else
      {
        log("Transitioning to Game (Sandbox).");
        curr = cs;
      }
      break;
    default:
      curr = cs;
      break;
    }
  };
}