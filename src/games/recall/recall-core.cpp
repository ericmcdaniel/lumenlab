#include "esp_system.h"

#include "games/recall/recall-core.h"
#include "common.h"
#include "logger.h"

namespace Games
{
  RecallCore::RecallCore(Core::ContextManager *ctx) : contextManager{ctx}
  {
    setupGameColors();
    contextManager->stateManager.getRecallGameState().reset();
    state = GameState::Startup;
    wait(playbackDurationIlluminated);
  }

  void RecallCore::setupGameColors()
  {
    // temporary for testing purposes
    for (uint16_t i = 0; i < maxRound; ++i)
    {
      gameplayColors[i] = static_cast<Player::ControllerButton>(i % arraySize(availableGameplayButtons));
    }

    // for (uint16_t i = 0; i < maxRound; ++i)
    // {
    //   auto colorIndex = esp_random() % arraySize(availableGameplayButtons);
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
    switch (state)
    {
    case GameState::Startup:
      if (isReady())
      {
        state = GameState::ComputerPlaybackOnDisplay;
        wait(playbackDurationIlluminated);
      }
      break;
    case GameState::ComputerPlaybackOnDisplay:
      displayComputerPlayback();
      break;
    case GameState::ComputerPlaybackPaused:
      pauseComputerPlayback();
      break;
    case GameState::Player:
      evaluateUserRecall();
      break;
    case GameState::GameOver:
      sequenceIndex = 0;
      contextManager->stateManager.getRecallGameState().reset();
      contextManager->stateManager.displayShouldUpdate = true;
      break;
    }
  }

  void RecallCore::displayComputerPlayback()
  {
    if (isReady())
    {
      state = GameState::ComputerPlaybackPaused;
      wait(playbackDurationPaused);
      return;
    }

    for (uint16_t i = 0; i <= contextManager->leds.size(); ++i)
    {
      auto color = colorPalette[static_cast<size_t>(gameplayColors[sequenceIndex])];
      contextManager->leds.buffer[i] = color;
    }
  }

  void RecallCore::pauseComputerPlayback()
  {
    if (sequenceIndex >= round)
    {
      state = GameState::Player;
      sequenceIndex = 0;
      contextManager->controller.reset();
      return;
    }

    if (isReady())
    {
      ++sequenceIndex;
      state = GameState::ComputerPlaybackOnDisplay;
      wait(playbackDurationIlluminated);
    }
  }

  void RecallCore::evaluateUserRecall()
  {
    illuminateOnSelection();

    if (sequenceIndex > round && isReady())
    {
      state = GameState::ComputerPlaybackOnDisplay;
      sequenceIndex = 0;
      incrementRound();
      colorPlaybackTimer.wait(playbackDurationPaused);
      contextManager->stateManager.displayShouldUpdate = true;
      wait(playbackDurationIlluminated);
      return;
    }

    evaluateUserButton(gameplayColors[sequenceIndex]);
  }

  void RecallCore::evaluateUserButton(Player::ControllerButton button)
  {
    if (contextManager->controller.wasPressedAndReleased(button))
    {
      ++sequenceIndex;
      wait(1000);
    }
    if (incorrectButtonWasPressed(button))
    {
      logf("Incorrect answer");
      state = GameState::GameOver;
    }
  }

  void RecallCore::incrementRound(uint16_t amount)
  {
    round += amount;
    contextManager->stateManager.getRecallGameState().round = round;
  }

  void RecallCore::illuminateOnSelection()
  {
    for (size_t btnIdx = 0; btnIdx < arraySize(availableGameplayButtons); ++btnIdx)
    {
      if (contextManager->controller.buttonState(static_cast<Player::ControllerButton>(btnIdx)) > 0)
        for (uint16_t i = 0; i <= contextManager->leds.size(); ++i)
          contextManager->leds.buffer[i] = colorPalette[btnIdx];
    }
  }

  bool RecallCore::incorrectButtonWasPressed(Player::ControllerButton correctButton)
  {

    bool correctPressed = contextManager->controller.wasPressed(correctButton);

    for (auto button : availableGameplayButtons)
    {
      if (button == correctButton)
        continue;
      if (contextManager->controller.wasPressed(button) && !correctPressed)
        return true;
    }

    return false;
  }
}