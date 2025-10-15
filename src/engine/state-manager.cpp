#include "engine/state-manager.h"
#include "logger.h"

namespace Engine
{
  void CoreStateManager::setNext(CoreStateOptions cs)
  {
    switch (cs)
    {
    case CoreStateOptions::GAME_SANDBOX:
      if (curr != CoreStateOptions::TRANSITION_SANDBOX)
        curr = CoreStateOptions::TRANSITION_SANDBOX;
      else
        curr = cs;
      break;
    default:
      curr = cs;
      break;
    }
  };
}