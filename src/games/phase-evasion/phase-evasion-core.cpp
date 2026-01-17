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
      getUpdates();
      renderFlare();
      checkCollision();
      renderUserColor();
      break;
    case PhaseEvasionStates::GameOver:
      for (uint16_t i = 0; i < contextManager->config.numLeds; ++i)
      {
        contextManager->leds.buffer[i] = Lights::ColorCode::GameRed;
      }
      break;
    }
  }

  void PhaseEvasionCore::getUpdates()
  {
    player.checkColorChangeRequest();
    flare.updatePosition();
  }

  void PhaseEvasionCore::renderUserColor()
  {
    for (uint16_t i = playerClearance; i < playerClearance + player.width; ++i)
    {
      contextManager->leds.buffer[i] = player.getColor();
    }
  }

  void PhaseEvasionCore::renderFlare()
  {
    uint16_t start = std::max(flare.getPosition() - flare.width, 0);
    uint16_t end = std::min(flare.getPosition(), contextManager->config.numLeds);

    for (uint16_t i = start; i < end; ++i)
    {
      contextManager->leds.buffer[i] = flare.getColor();
    }
  }

  void PhaseEvasionCore::checkCollision()
  {
    uint16_t start = std::max(flare.getPosition() - flare.width, 0);
    uint16_t end = std::min(flare.getPosition(), contextManager->config.numLeds);

    if (start <= playerClearance + player.width && end >= playerClearance && player.getColor() != flare.getColor())
    {
      state.current = PhaseEvasionStates::GameOver;
    }
  }
}