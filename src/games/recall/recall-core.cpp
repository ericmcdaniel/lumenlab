#include "esp_system.h"

#include "games/recall/recall-core.h"
#include "logger.h"

namespace Games
{
  RecallCore::RecallCore(Engine::StateManager &sm, Lights::LedStrip &l, const Player::Controller &c) : engineState{sm}, leds{l}, controller{c}
  {
    setupGameColors();
    engineState.getRecallGameState().reset();
    waitFromNow(playbackDurationTotal);
    colorPlaybackTimer.waitFromNow(playbackDurationIlluminated);
  }

  void RecallCore::setupGameColors()
  {
    // temporary for testing purposes
    for (uint16_t i = 0; i < maxRound; ++i)
    {
      gameplayColors[i] = i % 4;
    }

    // for (uint16_t i = 0; i < maxRound; ++i)
    // {
    //   auto colorIndex = esp_random() % 4;
    //   gameplayColors[i] = colorIndex;
    // }
    log("First 10 round RGB values for testing:");
    for (uint16_t i = 0; i < 10; ++i)
    {
      logf("Round %u: (%u - %u - %u)", i + 1, colorPalette[gameplayColors[i]].r, colorPalette[gameplayColors[i]].g, colorPalette[gameplayColors[i]].b);
    }
  }

  void RecallCore::nextEvent()
  {
    switch (activePlayer)
    {
    case ActivePlayer::Computer:
      printComputerPlayback();
      break;
    case ActivePlayer::Player:
      if (controller.wasPressed(Player::ControllerButton::Cross))
      {
        playbackRound = 0;
        ++engineState.getRecallGameState().round;
        engineState.displayShouldUpdate = true;
        activePlayer = ActivePlayer::Computer;
        logf("Round: %u", engineState.getRecallGameState().round + 1);

        waitFromNow(playbackDurationTotal);
        colorPlaybackTimer.waitFromNow(playbackDurationIlluminated);
      }
      break;
    }
  }

  void RecallCore::printComputerPlayback()
  {
    if (playbackRound > engineState.getRecallGameState().round)
    {
      activePlayer = ActivePlayer::Player;
      return;
    }

    if (!colorPlaybackTimer.isReady())
    {
      for (uint16_t i = 0; i <= leds.size(); ++i)
      {
        auto color = colorPalette[gameplayColors[playbackRound]];
        leds.buffer[i].r = color.r;
        leds.buffer[i].g = color.g;
        leds.buffer[i].b = color.b;
      }
    }

    if (isReady())
    {
      auto color = colorPalette[playbackRound % 4];
      logf("Computer displayed: (%u - %u - %u)", color.r, color.g, color.b);
      ++playbackRound;
      waitFromNow(playbackDurationTotal);
      colorPlaybackTimer.waitFromNow(playbackDurationIlluminated);
    }
  }
}