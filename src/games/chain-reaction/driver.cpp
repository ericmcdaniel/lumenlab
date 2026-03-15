#include "games/chain-reaction/driver.h"

namespace Games::ChainReaction
{
  Driver::Driver(SystemCore::ContextManager *ctx) : contextManager{ctx},
                                                    state{ctx->stateManager.getChainReactionGameState()} {}
}