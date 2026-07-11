#include "games/chain-reaction/game-main.h"
#include "logger.h"

namespace Games::ChainReaction
{
  GameMain::GameMain(SystemCore::ContextManager *ctx) : contextManager{ctx},
                                                        state{ctx->stateManager.getChainReactionGameState()},
                                                        cannon{ctx}
  {
    reset();
    wait(500);
  }

  void GameMain::nextEvent()
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

  void GameMain::advanceActiveIon()
  {
    for (auto &ion : cannon)
    {
      if (!ion.isActive())
        continue;

      ion.updatePosition();
    }
  }

  void GameMain::renderIons()
  {
    logf("# of Ions: %u", cannon.size());
    int ct = 1;
    for (const auto &ion : cannon)
    {
      logf("# of colors per ion: %u", ion.getSize());
      for (uint16_t i = 0; i < ion.getSize(); ++i)
      {

        uint16_t segmentHead = std::max(ion.getPosition() - ((ion.getSize() - i) * cannon.ionWidth), 0);
        uint16_t segmentTail = std::min(static_cast<uint16_t>(ion.getPosition() - ((ion.getSize() - i - 1) * cannon.ionWidth)), SystemCore::Configuration::numLeds());

        for (uint16_t j = segmentHead; j < segmentTail; ++j)
        {
          contextManager->renderer.leds.buffer[j] = ion.getColors().at(i);
        }
        logf("Ion %u - Color: %u", ct, ion.getColors().at(i));
      }
      ct++;
    }
  }

  void GameMain::reset()
  {
    state.reset();
    state.current = Actions::Startup;
    cannon.reset();
  }

  void GameMain::handleDispatch()
  {
    cannon.dispatch();
    state.current = Actions::ActiveDrop;
  }
}