#include "esp_system.h"

#include "games/recall/core.h"
#include "logger.h"

namespace Games
{
  RecallCore::RecallCore(Engine::StateManager &sm, Lights::LedStrip &l, const Player::Controller &c) : engineState{sm}, leds{l}, controller{c}
  {
    setupGameColors();
    engineState.getRecallGameState().reset();
    resettedWait(playbackDurationTotal);
    colorPlaybackTimer.resettedWait(playbackDurationIlluminated);
  }

  void RecallCore::setupGameColors()
  {
    // temporary for testing purposes
    static constexpr uint8_t testValues[20] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
    for (size_t i = 0; i < 256; ++i)
    {
      gameplayColors[i] = colorPalette[testValues[i]];
    }

    // for (size_t i = 0; i < 256; ++i)
    // {
    //   auto colorIndex = esp_random() % 4;
    //   gameplayColors[i] = colorPalette[colorIndex];
    // }
    // logf("1st RGB: (%u - %u - %u)", gameplayColors[0].r, gameplayColors[0].g, gameplayColors[0].b);
    // logf("2nd RGB: (%u - %u - %u)", gameplayColors[1].r, gameplayColors[1].g, gameplayColors[1].b);
    // logf("3rd RGB: (%u - %u - %u)", gameplayColors[2].r, gameplayColors[2].g, gameplayColors[2].b);
  }

  void RecallCore::nextEvent()
  {
    if (!isPlayersTurn && playbackRound <= engineState.getRecallGameState().round)
    {
      if (!colorPlaybackTimer.isReady())
      {
        for (int i = 0; i <= leds.size(); ++i)
        {
          leds.buffer[i].r = gameplayColors[playbackRound].r;
          leds.buffer[i].g = gameplayColors[playbackRound].g;
          leds.buffer[i].b = gameplayColors[playbackRound].b;
        }
      }
      if (isReady())
      {
        logf("Computer displayed: (%u - %u - %u)", gameplayColors[playbackRound].r, gameplayColors[playbackRound].g, gameplayColors[playbackRound].b);
        ++playbackRound;
        resettedWait(playbackDurationTotal);
        colorPlaybackTimer.resettedWait(playbackDurationIlluminated);
      }
    }
    else
    {
      isPlayersTurn = !isPlayersTurn;
    }

    if (isPlayersTurn)
    {
      if (controller.wasPressed(Player::ControllerButton::Cross))
      {
        playbackRound = 0;
        ++engineState.getRecallGameState().round;
        engineState.displayShouldUpdate = true;
        logf("Round: %u", engineState.getRecallGameState().round + 1);
        resettedWait(playbackDurationTotal);
        colorPlaybackTimer.resettedWait(playbackDurationIlluminated);
      }
    }
  }
}