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
        state.current = Actions::Dispatch;
        log("Starting new game.");
      }
      break;
    case Actions::Dispatch:
      handleDispatch();
      return;
    case Actions::ActiveDrop:
      advanceActiveIon();
      renderIons();
      return;
    default:
      return;
    }
  }

  void Driver::advanceActiveIon()
  {
    for (auto &ion : cannon)
    {
      if (!ion.isActive())
        continue;

      ion.updatePosition();
    }
  }

  void Driver::renderIons()
  {
    for (const auto &ion : cannon)
    {
      uint16_t ionHead = std::max(ion.getPosition() - ion.width, 0);
      uint16_t ionTail = std::min(ion.getPosition(), SystemCore::Configuration::numLeds());

      for (uint16_t i = ionHead; i < ionTail; ++i)
      {
        contextManager->leds.buffer[i] = Lights::ColorCode::ThemeYellow;
      }
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
    cannon.dispatch();
    state.current = Actions::ActiveDrop;
  }
}