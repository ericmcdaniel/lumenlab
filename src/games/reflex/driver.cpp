#include "games/reflex/driver.h"
#include "games/reflex/signal.h"
#include "logger.h"

namespace Games::Reflex
{
  Driver::Driver(SystemCore::ContextManager *ctx) : contextManager{ctx},
                                                    state{ctx->stateManager.getReflexGameState()}
  {
    reset();
    wait(500);
  }

  void Driver::nextEvent()
  {
    switch (state.current)
    {
    case Actions::Startup:
      if (isReady())
      {
        reset();
        state.current = Actions::ActiveGame;
        log("Starting new game.");
      }
      break;
    case Actions::ActiveGame:
      break;
    default:
      break;
    }
  }

  void Driver::reset()
  {
    contextManager->stateManager.displayShouldUpdate = true;
  }
}