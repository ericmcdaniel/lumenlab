#include "games/reflex/driver.h"
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
        state.current = Actions::GameOver;
        log("Starting new game.");
      }
      break;
    default:
      break;
    }
  }
}