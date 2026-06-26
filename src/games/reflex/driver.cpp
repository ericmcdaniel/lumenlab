#include "games/reflex/driver.h"
#include "games/reflex/signal.h"
#include "logger.h"

namespace Games::Reflex
{
  Driver::Driver(SystemCore::ContextManager *ctx) : contextManager{ctx},
                                                    state{ctx->stateManager.getReflexGameState()},
                                                    signal{ctx, signalWidth, signalSpeed}
  {
    reset();
  }

  void Driver::nextEvent()
  {
    switch (state.current)
    {
    case Actions::Startup:
      if (isReady())
      {
        reset();
        state.current = Actions::Ready;
        wait(1000);
        log("Starting new game.");
      }
      break;
    case Actions::Ready:
      if (isReady())
      {
        state.current = Actions::ActiveGame;
      }
      renderSignal();
      break;
    case Actions::ActiveGame:
      signal.advance();
      renderSignal();
      break;
    default:
      break;
    }
  }

  void Driver::reset()
  {
    contextManager->stateManager.displayShouldUpdate = true;
  }

  void Driver::renderSignal()
  {
    for (uint16_t i = 0; i < signal.width; ++i)
    {
      uint16_t index = (signal.getPosition() + i) % SystemCore::Configuration::numLeds();
      contextManager->leds.buffer[index] = Lights::ColorCode::MenuUnselected;
    }
  }
}