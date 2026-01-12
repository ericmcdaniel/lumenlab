#include "games/phase-evasion/phase-evasion-core.h"
#include "logger.h"

namespace Games
{
  PhaseEvasionCore::PhaseEvasionCore(Core::ContextManager *ctx) : contextManager{ctx},
                                                                  player{ctx},
                                                                  flare{ctx}
  {
    state = contextManager->stateManager.getPhaseEvasionGameState();
    state.reset();
    state.current = PhaseEvasionStates::Startup;
    wait(500);
  }

  void PhaseEvasionCore::nextEvent()
  {
    switch (state.current)
    {
    case PhaseEvasionStates::Startup:
      if (isReady())
      {
        state.current = PhaseEvasionStates::ActiveGame;
        log("Starting new game.");
      }
      break;
    case PhaseEvasionStates::ActiveGame:
      player.checkColorChangeRequest();
      flare.updatePosition();
      checkCollision();
      renderFlare();
      renderUserColor();
      break;
    }
  }

  void PhaseEvasionCore::renderUserColor()
  {
    for (uint16_t i = clearance; i < clearance + player.width; ++i)
    {
      contextManager->leds.buffer[i] = player.getColor();
    }
  }

  void PhaseEvasionCore::renderFlare()
  {
    for (uint16_t i = flare.getPosition() - flare.width; i < flare.getPosition(); ++i)
    {
      contextManager->leds.buffer[i] = Lights::ColorCode::GameRed;
    }
  }

  void PhaseEvasionCore::checkCollision()
  {
    // if ()
  }
}