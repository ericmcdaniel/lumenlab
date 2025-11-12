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
    // for (uint16_t i = 0; i < maxRound; ++i)
    // {
    //   gameplayColors[i] = static_cast<Player::ControllerButton>(i % arraySize(availableGameplayButtons));
    // }

    for (uint16_t i = 0; i < maxRound; ++i)
    {
      uint16_t colorIndex = static_cast<uint16_t>(esp_random()) % arraySize(availableGameplayButtons);
      gameplayColors[i] = static_cast<Player::ControllerButton>(colorIndex);
    }
    auto button = gameplayColors[0];
    auto &color = colorPalette[static_cast<uint16_t>(button)];
    log("First round's RGB color:");
    logf("    Color=%u (%u - %u - %u)", button, color.r(), color.g(), color.b());
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
    case GameState::PlayerResponseEvaluation:
      evaluateUserRecall();
      break;
    case GameState::PlayerResponseVerified:
      prepareComputerPlayback();
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

    auto boundaries = directionBoundaries(gameplayColors[sequenceIndex]);
    double mu = (boundaries.first + boundaries.second) / 2.0;
    double delta = ((gameplayColors[sequenceIndex] ==
                         Player::ControllerButton::Circle ||
                     gameplayColors[sequenceIndex] == Player::ControllerButton::Square)
                        ? contextManager->config.recallBoundaries[2] - contextManager->config.recallBoundaries[1]
                        : contextManager->config.recallBoundaries[1] - contextManager->config.recallBoundaries[0]) /
                   5;

    for (uint16_t i = boundaries.first; i <= boundaries.second; ++i)
    {
      double x = static_cast<double>(i);
      double scope = std::exp(-0.5 * std::pow((x - mu) / delta, 2.0));
      auto color = colorPalette[static_cast<uint16_t>(gameplayColors[sequenceIndex])];
      contextManager->leds.buffer[i] = color * scope;
    }
  }

  void RecallCore::pauseComputerPlayback()
  {
    if (sequenceIndex >= state.round)
    {
      state.current = GameState::PlayerResponseEvaluation;
      sequenceIndex = 0;
      contextManager->controller.reset();
      successFadeawayAnimation = 1;
      log("Ready for User playback");
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
      state.current = GameState::PlayerResponseVerified;
      ++state.round;
      contextManager->stateManager.displayShouldUpdate = true;
      contextManager->controller.reset();
      wait(playbackDurationIlluminated * 2);
      return;
    }

    illuminateOnSelection();
    evaluateUserButton(gameplayColors[sequenceIndex]);
  }

  void RecallCore::evaluateUserButton(Player::ControllerButton expectedButton)
  {
    for (auto button : availableGameplayButtons)
    {
      if (contextManager->controller.wasPressed(button))
      {
        if (button == expectedButton)
        {
          ++sequenceIndex;
          auto &color = colorPalette[static_cast<uint16_t>(button)];
          logf("User correctly responded with color=%u (%u - %u - %u)", button, color.r(), color.g(), color.b());
          wait(playbackDurationPaused);
          return;
        }

        logf("User provided the incorrect answer. Entering game over sequence.");
        state.current = GameState::GameOver;
      }
    }
  }

  void RecallCore::illuminateOnSelection()
  {
    static uint32_t lastLightTime = 0;
    static int pressedButtonIndex = -1;
    bool buttonPressed = false;

    for (uint16_t i = 0; i < arraySize(availableGameplayButtons); ++i)
    {
      if (contextManager->controller.rawButtonState(static_cast<Player::ControllerButton>(i)) > 0)
      {
        pressedButtonIndex = i;
        lastLightTime = millis();
        buttonPressed = true;
        break;
      }
    }

    bool keepLit = ((millis() - lastLightTime) < playbackDurationPaused);
    if (buttonPressed || keepLit)
    {
      auto boundaries = directionBoundaries(static_cast<Player::ControllerButton>(pressedButtonIndex));
      for (uint16_t i = boundaries.first; i <= boundaries.second; ++i)
        contextManager->leds.buffer[i] = colorPalette[pressedButtonIndex];
    }
  }

  std::pair<uint16_t, uint16_t> RecallCore::directionBoundaries(Player::ControllerButton button)
  {
    const auto &boundary = contextManager->config.recallBoundaries;

    switch (button)
    {
    case Player::ControllerButton::Triangle:
      return {boundary[0], static_cast<uint16_t>(boundary[1] - 1)};
    case Player::ControllerButton::Circle:
      return {boundary[1], static_cast<uint16_t>(boundary[2] - 1)};
    case Player::ControllerButton::Cross:
      return {boundary[2], static_cast<uint16_t>(boundary[3] - 1)};
    case Player::ControllerButton::Square:
      return {boundary[3], static_cast<uint16_t>(contextManager->leds.size() - 1)};
    default:
      return {0, 0};
    }
  }

  void RecallCore::prepareComputerPlayback()
  {
    if (isReady())
    {
      logf("Round %u color sequence:", sequenceIndex);
      for (int i = 0; i <= sequenceIndex; ++i)
      {
        auto button = gameplayColors[i];
        auto &color = colorPalette[static_cast<uint16_t>(button)];
        logf("    Color=%u (%u - %u - %u)", button, color.r(), color.g(), color.b());
      }
      state.current = GameState::ComputerPlaybackOnDisplay;
      sequenceIndex = 0;
      wait(playbackDurationIlluminated);
      return;
    }

    auto boundaries = directionBoundaries(gameplayColors[sequenceIndex - 1]);
    for (uint16_t i = boundaries.first; i <= boundaries.second; ++i)
    {
      auto &color = colorPalette[static_cast<uint16_t>(gameplayColors[sequenceIndex - 1])];
      contextManager->leds.buffer[i] = color * successFadeawayAnimation;
    }
    successFadeawayAnimation = std::clamp(successFadeawayAnimation - 0.08, 0.0, 1.0);
  }

  void RecallCore::gameOver()
  {
    if (contextManager->controller.wasPressed(Player::ControllerButton::Start))
    {
      state.current = GameState::Startup;
      sequenceIndex = 0;
      state.reset();
      contextManager->stateManager.getRecallGameState().reset();
      setupGameColors();
      contextManager->stateManager.displayShouldUpdate = true;
    }

    for (int i = 0; i <= contextManager->leds.size(); ++i)
    {
      float phase = std::cos((2 * M_PI * i / contextManager->leds.size()) + (2 * M_PI * gameOverLedPhaseShift / contextManager->leds.size())) * 127 + 128;
      contextManager->leds.buffer[i] = {static_cast<uint8_t>(std::floor(phase)), 0, 0};
    }
    gameOverLedPhaseShift = std::clamp(gameOverLedPhaseShift + 0.5, 0.0, static_cast<double>(contextManager->leds.size()));
  }
}