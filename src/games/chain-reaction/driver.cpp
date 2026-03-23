#include "games/chain-reaction/driver.h"
#include "logger.h"

namespace Games::ChainReaction
{
  Driver::Driver(SystemCore::ContextManager *ctx) : contextManager{ctx},
                                                    state{ctx->stateManager.getChainReactionGameState()}
  {
    state.reset();
    state.current = Actions::Startup;
    wait(500);
  }

  void Driver::nextEvent()
  {
    switch (state.current)
    {
    case Actions::Startup:
      if (isReady())
      {
        state.current = Actions::ActiveGame;
        state.reset();
        log("Starting new game.");
      }
      break;
    case Actions::ActiveGame:
      return;
    default:
      return;
    }
  }
}