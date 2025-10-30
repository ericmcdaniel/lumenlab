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
      logf("Round %u: Color=%u (%u - %u - %u)", i + 1, gameplayColors[i], colorPalette[gameplayColors[i]].r, colorPalette[gameplayColors[i]].g, colorPalette[gameplayColors[i]].b);
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
      evaluateUserRecall();
      break;
    case ActivePlayer::None:
      // waitFromNow(1000);
      // activePlayer = ActivePlayer::Computer;
      playbackRound = 0;
      contextManager->stateManager.getRecallGameState().reset();
      contextManager->stateManager.displayShouldUpdate = true;
      break;
    }
  }

  void RecallCore::printComputerPlayback()
  {
    if (playbackRound > round)
    {
      activePlayer = ActivePlayer::Player;
      playbackRound = 0;
      contextManager->controller.reset();
      return;
    }

    if (!colorPlaybackTimer.isReady())
    {
      for (uint16_t i = 0; i <= contextManager->leds.size(); ++i)
      {
        auto color = colorPalette[gameplayColors[playbackRound]];
        contextManager->leds.buffer[i] = color;
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

  void RecallCore::evaluateUserRecall()
  {
    displayButtonKeypress();

    if (playbackRound > round && isReady())
    {
      activePlayer = ActivePlayer::Computer;
      playbackRound = 0;
      incrementRound();
      waitFromNow(playbackDurationTotal);
      colorPlaybackTimer.waitFromNow(playbackDurationIlluminated);
      contextManager->stateManager.displayShouldUpdate = true;
      return;
    }

    switch (gameplayColors[playbackRound])
    {
    case 0:
      if (contextManager->controller.wasPressedAndReleased(Player::ControllerButton::Cross))
      {
        ++playbackRound;
        waitFromNow(1000);
      }
      if (incorrectButtonWasPressed(Player::ControllerButton::Cross))
      {
        logf("Incorrect answer");
        activePlayer = ActivePlayer::None;
      }
      break;
    case 1:
      if (contextManager->controller.wasPressedAndReleased(Player::ControllerButton::Square))
      {
        ++playbackRound;
        waitFromNow(1000);
      }
      if (incorrectButtonWasPressed(Player::ControllerButton::Square))
      {
        logf("Incorrect answer");
        activePlayer = ActivePlayer::None;
      }
      break;
    case 2:
      if (contextManager->controller.wasPressedAndReleased(Player::ControllerButton::Triangle))
      {
        ++playbackRound;
        waitFromNow(1000);
      }
      if (incorrectButtonWasPressed(Player::ControllerButton::Triangle))
      {
        logf("Incorrect answer");
        activePlayer = ActivePlayer::None;
      }
      break;
    case 3:
      if (contextManager->controller.wasPressedAndReleased(Player::ControllerButton::Circle))
      {
        ++playbackRound;
        waitFromNow(1000);
      }
      if (incorrectButtonWasPressed(Player::ControllerButton::Circle))
      {
        logf("Incorrect answer");
        activePlayer = ActivePlayer::None;
      }
      break;
    }
  }

  void RecallCore::incrementRound(uint16_t amount)
  {
    round += amount;
    contextManager->stateManager.getRecallGameState().round = round;
  }

  void RecallCore::displayButtonKeypress()
  {
    if (contextManager->controller.buttonState(Player::ControllerButton::Cross) > 0)
      for (uint16_t i = 0; i <= contextManager->leds.size(); ++i)
        contextManager->leds.buffer[i] = colorPalette[0];
    else if (contextManager->controller.buttonState(Player::ControllerButton::Square) > 0)
      for (uint16_t i = 0; i <= contextManager->leds.size(); ++i)
        contextManager->leds.buffer[i] = colorPalette[1];
    else if (contextManager->controller.buttonState(Player::ControllerButton::Triangle) > 0)
      for (uint16_t i = 0; i <= contextManager->leds.size(); ++i)
        contextManager->leds.buffer[i] = colorPalette[2];
    else if (contextManager->controller.buttonState(Player::ControllerButton::Circle) > 0)
      for (uint16_t i = 0; i <= contextManager->leds.size(); ++i)
        contextManager->leds.buffer[i] = colorPalette[3];
  }

  bool RecallCore::incorrectButtonWasPressed(Player::ControllerButton correctButton)
  {
    switch (correctButton)
    {
    case Player::ControllerButton::Cross:
      return !contextManager->controller.wasPressed(Player::ControllerButton::Cross) &&
             (contextManager->controller.wasPressed(Player::ControllerButton::Square) ||
              contextManager->controller.wasPressed(Player::ControllerButton::Triangle) ||
              contextManager->controller.wasPressed(Player::ControllerButton::Circle));
    case Player::ControllerButton::Square:
      return !contextManager->controller.wasPressed(Player::ControllerButton::Square) &&
             (contextManager->controller.wasPressed(Player::ControllerButton::Cross) ||
              contextManager->controller.wasPressed(Player::ControllerButton::Triangle) ||
              contextManager->controller.wasPressed(Player::ControllerButton::Circle));
    case Player::ControllerButton::Triangle:
      return !contextManager->controller.wasPressed(Player::ControllerButton::Triangle) &&
             (contextManager->controller.wasPressed(Player::ControllerButton::Cross) ||
              contextManager->controller.wasPressed(Player::ControllerButton::Square) ||
              contextManager->controller.wasPressed(Player::ControllerButton::Circle));
    case Player::ControllerButton::Circle:
      return !contextManager->controller.wasPressed(Player::ControllerButton::Circle) &&
             (contextManager->controller.wasPressed(Player::ControllerButton::Cross) ||
              contextManager->controller.wasPressed(Player::ControllerButton::Square) ||
              contextManager->controller.wasPressed(Player::ControllerButton::Triangle));
    }
    return false;
  }
}