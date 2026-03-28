#include "games/chain-reaction/driver.h"
#include "logger.h"

namespace Games::ChainReaction
{
  Driver::Driver(SystemCore::ContextManager *ctx) : contextManager{ctx},
                                                    state{ctx->stateManager.getChainReactionGameState()},
                                                    cannon{ctx}
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
      handleDispatch();
      return;
    default:
      return;
    }
  }

  void Driver::reset()
  {
    state.reset();
    state.current = Actions::Startup;
    cannon.reset();
  }

  void Driver::handleDispatch()
  {
    // if ()
  }
}