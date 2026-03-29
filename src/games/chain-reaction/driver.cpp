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
      break;
    case Actions::ActiveDrop:
      advanceActiveIon();
      renderIons();
      break;
    default:
      break;
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
      for (uint16_t i = 0; i < ion.getSize(); ++i)
      {

        uint16_t segmentHead = std::max(ion.getPosition() - ((ion.getSize() - i) * cannon.ionWidth), 0);
        uint16_t segmentTail = std::min(static_cast<uint16_t>(ion.getPosition() - ((ion.getSize() - i - 1) * cannon.ionWidth)), SystemCore::Configuration::numLeds());

        for (uint16_t j = segmentHead; j < segmentTail; ++j)
        {
          contextManager->leds.buffer[j] = ion.getColors().at(i);
        }
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