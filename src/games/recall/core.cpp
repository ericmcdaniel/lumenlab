#include "esp_system.h"

#include "games/recall/core.h"
#include "logger.h"

namespace Games
{
  RecallCore::RecallCore(Engine::StateManager &sm, Lights::LedStrip &l, const Player::Controller &c) : engineState{sm}, leds{l}, controller{c}
  {
    setupGameColors();
    engineState.getRecallGameState().reset();
    wait(1000);
  }

  void RecallCore::setupGameColors()
  {
    for (size_t i = 0; i < 256; ++i)
    {
      auto colorIndex = esp_random() % 4;
      gameplayColors[i] = colorPalette[colorIndex];
    }
  }

  void RecallCore::nextEvent()
  {
    for (int i = 0; i <= leds.size(); ++i)
    {
      leds.buffer[i].r = gameplayColors[playbackRound].r;
      leds.buffer[i].g = gameplayColors[playbackRound].g;
      leds.buffer[i].b = gameplayColors[playbackRound].b;
    }
    if (isReady())
    {
      ++playbackRound;
      wait(1000);
    }

    if (!engineState.getRecallGameState().isPlayersTurn)
    {
      if (controller.wasPressed(Player::ControllerButton::Cross))
      {
        ++engineState.getRecallGameState().round;
        engineState.displayShouldUpdate = true;
        logf("Current score: %u", engineState.getRecallGameState().round);
      }
    }
  }
}