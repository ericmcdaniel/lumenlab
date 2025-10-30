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
      gameplayColors[i] = static_cast<Player::ControllerButton>(i % 4);
    }

    // for (uint16_t i = 0; i < maxRound; ++i)
    // {
    //   auto colorIndex = esp_random() % 4;
    //   gameplayColors[i] = colorIndex;
    // }
    log("First 10 round RGB values for testing:");
    for (uint16_t i = 0; i < 10; ++i)
    {
      logf("Round %u: Color=%u (%u - %u - %u)", i + 1, gameplayColors[i],
           colorPalette[static_cast<size_t>(gameplayColors[i])].r,
           colorPalette[static_cast<size_t>(gameplayColors[i])].g,
           colorPalette[static_cast<size_t>(gameplayColors[i])].b);
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
        auto color = colorPalette[static_cast<size_t>(gameplayColors[playbackRound])];
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

    evaluateUserButton(gameplayColors[playbackRound]);
  }

  void RecallCore::evaluateUserButton(Player::ControllerButton button)
  {
    if (contextManager->controller.wasPressedAndReleased(button))
    {
      ++playbackRound;
      waitFromNow(1000);
    }
    if (incorrectButtonWasPressed(button))
    {
      logf("Incorrect answer");
      activePlayer = ActivePlayer::None;
    }
  }

  void RecallCore::incrementRound(uint16_t amount)
  {
    round += amount;
    contextManager->stateManager.getRecallGameState().round = round;
  }

  void RecallCore::displayButtonKeypress()
  {
    for (size_t btnIdx = 0; btnIdx < 4; ++btnIdx)
    {
      if (contextManager->controller.buttonState(static_cast<Player::ControllerButton>(btnIdx)) > 0)
        for (uint16_t i = 0; i <= contextManager->leds.size(); ++i)
          contextManager->leds.buffer[i] = colorPalette[btnIdx];
    }
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