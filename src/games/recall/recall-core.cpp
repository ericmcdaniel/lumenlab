#include "esp_system.h"

#include "games/recall/recall-core.h"
#include "common.h"
#include "logger.h"

namespace Games
{
  RecallCore::RecallCore(Core::ContextManager *ctx) : contextManager{ctx}
  {
    setupGameColors();
    state = contextManager->stateManager.getRecallGameState();
    state.reset();
    state.current = GameState::Startup;
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
    //   uint16_t colorIndex = static_cast<uint16_t>(esp_random()) % arraySize(availableGameplayButtons);
    //   gameplayColors[i] = static_cast<Player::ControllerButton>(colorIndex);
    // }
    log("First 10 round RGB values for testing:");
    for (uint16_t i = 0; i < 10; ++i)
    {
      logf("Round %u: Color=%u (%u - %u - %u)", i + 1, gameplayColors[i],
           colorPalette[static_cast<uint16_t>(gameplayColors[i])].r,
           colorPalette[static_cast<uint16_t>(gameplayColors[i])].g,
           colorPalette[static_cast<uint16_t>(gameplayColors[i])].b);
    }
  }

  void RecallCore::nextEvent()
  {
    switch (state.current)
    {
    case GameState::Startup:
      if (isReady())
      {
        state.current = GameState::ComputerPlaybackOnDisplay;
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
      gameOver();
      break;
    }
  }

  void RecallCore::displayComputerPlayback()
  {
    if (isReady())
    {
      state.current = GameState::ComputerPlaybackPaused;
      wait(playbackDurationPaused);
      return;
    }

    for (uint16_t i = 0; i <= contextManager->leds.size(); ++i)
    {
      auto color = colorPalette[static_cast<uint16_t>(gameplayColors[sequenceIndex])];
      contextManager->leds.buffer[i] = color;
    }
  }

  void RecallCore::pauseComputerPlayback()
  {
    if (sequenceIndex >= state.round)
    {
      state.current = GameState::Player;
      sequenceIndex = 0;
      contextManager->controller.reset();
      return;
    }

    if (isReady())
    {
      ++sequenceIndex;
      state.current = GameState::ComputerPlaybackOnDisplay;
      wait(playbackDurationIlluminated);
    }
  }

  void RecallCore::evaluateUserRecall()
  {
    if (sequenceIndex > state.round && isReady())
    {
      state.current = GameState::ComputerPlaybackOnDisplay;
      sequenceIndex = 0;
      ++state.round;
      contextManager->stateManager.displayShouldUpdate = true;
      contextManager->controller.reset();
      wait(playbackDurationIlluminated);
      return;
    }

    evaluateUserButton(gameplayColors[sequenceIndex]);
    illuminateOnSelection();
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
      state.current = GameState::GameOver;
    }
  }

  void RecallCore::illuminateOnSelection()
  {
    for (uint16_t btnIdx = 0; btnIdx < arraySize(availableGameplayButtons); ++btnIdx)
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

  void RecallCore::gameOver()
  {
    if (contextManager->controller.wasPressed(Player::ControllerButton::Start))
    {
      state.current = GameState::Startup;
      sequenceIndex = 0;
      state.reset();
      contextManager->stateManager.getRecallGameState().reset();
      contextManager->stateManager.displayShouldUpdate = true;
    }

    for (int i = 0; i <= contextManager->leds.size(); ++i)
    {
      float phase = std::cos((2 * M_PI * i / 300) + (2 * M_PI * gameOverLedPhaseShift / 300)) * 127 + 128;
      contextManager->leds.buffer[i].r = std::floor(phase);
      contextManager->leds.buffer[i].g = 0;
      contextManager->leds.buffer[i].b = 0;
    }
    gameOverLedPhaseShift += 0.5;

    if (gameOverLedPhaseShift > 300)
      gameOverLedPhaseShift = 0;
  }
}