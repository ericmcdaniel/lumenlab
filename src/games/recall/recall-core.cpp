#include "esp_system.h"

#include "games/recall/recall-core.h"
#include "logger.h"

namespace Games
{
  RecallCore::RecallCore(Core::ContextManager *ctx) : contextManager{ctx}
  {
    setupGameColors();
    contextManager->stateManager.getRecallGameState().reset();
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
      if (contextManager->controller.wasPressed(Player::ControllerButton::Cross))
      {
        playbackRound = 0;
        ++contextManager->stateManager.getRecallGameState().round;
        contextManager->stateManager.displayShouldUpdate = true;
        activePlayer = ActivePlayer::Computer;
        logf("Round: %u", contextManager->stateManager.getRecallGameState().round + 1);

        waitFromNow(playbackDurationTotal);
        colorPlaybackTimer.waitFromNow(playbackDurationIlluminated);
      }
      break;
    }
  }

  void RecallCore::printComputerPlayback()
  {
    if (playbackRound > contextManager->stateManager.getRecallGameState().round)
    {
      activePlayer = ActivePlayer::Player;
      return;
    }

    if (!colorPlaybackTimer.isReady())
    {
      for (uint16_t i = 0; i <= contextManager->leds.size(); ++i)
      {
        auto color = colorPalette[gameplayColors[playbackRound]];
        contextManager->leds.buffer[i].r = color.r;
        contextManager->leds.buffer[i].g = color.g;
        contextManager->leds.buffer[i].b = color.b;
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