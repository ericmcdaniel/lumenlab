#include "esp_system.h"

#include "games/recall/controller.h"
#include "common.h"
#include "logger.h"

namespace Games::Recall
{
  Controller::Controller(SystemCore::ContextManager *ctx) : contextManager{ctx}
  {
    setupGameColors();
    state = contextManager->stateManager.getRecallGameState();
    state.reset();
    state.current = Actions::Startup;
    wait(gameplaySpeedIlluminated);
  }

  void Controller::setupGameColors()
  {
    for (uint16_t i = 0; i < maxRound; ++i)
    {
      // for testing
      // gameplayColors[i] = static_cast<Player::ControllerButton>(i % arraySize(availableGameplayButtons));

      uint16_t colorIndex = static_cast<uint16_t>(esp_random()) % arraySize(availableGameplayButtons);
      gameplayColors[i] = static_cast<Player::ControllerButton>(colorIndex);
    }
    auto button = gameplayColors[0];
    auto &color = Lights::colorPalette[static_cast<uint16_t>(button)];
    log("First round's RGB color:");
    logf("    Color=%u (%u - %u - %u)", button, color.r, color.g, color.b);
  }

  void Controller::nextEvent()
  {
    handleUserSpeedChange();
    switch (state.current)
    {
    case Actions::Startup:
      if (isReady())
      {
        state.current = Actions::ComputerPlaybackOnDisplay;
        wait(gameplaySpeedIlluminated);
      }
      break;
    case Actions::ComputerPlaybackOnDisplay:
      displayComputerPlayback();
      break;
    case Actions::ComputerPlaybackPaused:
      pauseComputerPlayback();
      break;
    case Actions::PlayerResponseEvaluation:
      evaluateUserRecall();
      break;
    case Actions::PlayerResponseVerified:
      prepareComputerPlayback();
      break;
    case Actions::GameOver:
      gameOver();
      break;
    }
  }

  void Controller::handleUserSpeedChange()
  {
    if (contextManager->controller.wasPressed(Player::ControllerButton::Up) || contextManager->controller.leftAnalog().y < -64)
    {
      // allow no faster than 200ms cycles
      if (gameplaySpeedIlluminated >= 200)
        gameplaySpeedIlluminated -= 10;
    }
    else if (contextManager->controller.wasPressed(Player::ControllerButton::Down) || contextManager->controller.leftAnalog().y > 64)
    {
      // similary, allow cycles to be no slower than 1.5 seconds
      if (gameplaySpeedIlluminated < 1500)
        gameplaySpeedIlluminated += 10;
    }
  }

  void Controller::displayComputerPlayback()
  {
    if (isReady())
    {
      state.current = Actions::ComputerPlaybackPaused;
      wait(gameplaySpeedPaused);
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
      auto color = Lights::colorPalette[static_cast<uint16_t>(gameplayColors[sequenceIndex])];
      contextManager->leds.buffer[i] = color * scope;
    }
  }

  void Controller::pauseComputerPlayback()
  {
    if (sequenceIndex >= state.round)
    {
      state.current = Actions::PlayerResponseEvaluation;
      sequenceIndex = 0;
      contextManager->controller.reset();
      successFadeawayAnimation = 1;
      log("Ready for User playback");
      return;
    }

    if (isReady())
    {
      ++sequenceIndex;
      state.current = Actions::ComputerPlaybackOnDisplay;
      wait(gameplaySpeedIlluminated);
    }
  }

  void Controller::evaluateUserRecall()
  {
    if (sequenceIndex > state.round && isReady())
    {
      state.current = Actions::PlayerResponseVerified;
      ++state.round;
      contextManager->stateManager.displayShouldUpdate = true;
      contextManager->controller.reset();
      wait(gameplaySpeedIlluminated * 2);
      return;
    }

    illuminateOnSelection();
    evaluateUserButton(gameplayColors[sequenceIndex]);
  }

  void Controller::evaluateUserButton(Player::ControllerButton expectedButton)
  {
    for (auto button : availableGameplayButtons)
    {
      if (contextManager->controller.wasPressedAndReleased(button))
      {
        if (button == expectedButton)
        {
          ++sequenceIndex;
          auto &color = Lights::colorPalette[static_cast<uint16_t>(button)];
          logf("User correctly responded with color=%u (%u - %u - %u)", button, color.r, color.g, color.b);
          wait(gameplaySpeedPaused);
          return;
        }

        logf("User provided the incorrect answer. Entering game over sequence.");
        state.current = Actions::GameOver;
      }
    }
  }

  void Controller::illuminateOnSelection()
  {
    static uint32_t lastLightTime = 0;
    static int pressedButtonIndex = -1;
    bool buttonPressed = false;
    for (uint16_t i = 0; i < arraySize(availableGameplayButtons); ++i)
    {
      auto btn = static_cast<Player::ControllerButton>(i);
      if (contextManager->controller.isDown(btn))
      {
        pressedButtonIndex = i;
        lastLightTime = millis();
        buttonPressed = true;
        break;
      }
    }

    bool keepLit = ((millis() - lastLightTime) < gameplaySpeedPaused);
    if (buttonPressed || keepLit)
    {
      if (pressedButtonIndex >= 0 && pressedButtonIndex < static_cast<int>(arraySize(availableGameplayButtons)))
      {
        auto boundaries = directionBoundaries(static_cast<Player::ControllerButton>(pressedButtonIndex));
        for (uint16_t i = boundaries.first; i <= boundaries.second; ++i)
          contextManager->leds.buffer[i] = Lights::colorPalette[pressedButtonIndex];
      }
    }
  }

  std::pair<uint16_t, uint16_t> Controller::directionBoundaries(Player::ControllerButton button)
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

  void Controller::prepareComputerPlayback()
  {
    if (isReady())
    {
      logf("Round %u color sequence:", sequenceIndex);
      for (int i = 0; i <= sequenceIndex; ++i)
      {
        auto button = gameplayColors[i];
        auto &color = Lights::colorPalette[static_cast<uint16_t>(button)];
        logf("    Color=%u (%u - %u - %u)", button, color.r, color.g, color.b);
      }
      state.current = Actions::ComputerPlaybackOnDisplay;
      sequenceIndex = 0;
      wait(gameplaySpeedIlluminated);
      return;
    }

    auto boundaries = directionBoundaries(gameplayColors[sequenceIndex - 1]);
    for (uint16_t i = boundaries.first; i <= boundaries.second; ++i)
    {
      auto &color = Lights::colorPalette[static_cast<uint16_t>(gameplayColors[sequenceIndex - 1])];
      contextManager->leds.buffer[i] = color * successFadeawayAnimation;
    }
    successFadeawayAnimation = std::clamp(successFadeawayAnimation - 0.08, 0.0, 1.0);
  }

  void Controller::gameOver()
  {
    if (contextManager->controller.wasPressed(Player::ControllerButton::Start))
    {
      state.current = Actions::Startup;
      sequenceIndex = 0;
      state.reset();
      contextManager->stateManager.getRecallGameState().reset();
      setupGameColors();
      contextManager->stateManager.displayShouldUpdate = true;
    }

    for (uint16_t i = 0; i <= contextManager->leds.size(); ++i)
    {
      float phase = std::cos((2.0f * M_PI * i / contextManager->leds.size()) + (2.0f * M_PI * gameOverLedPhaseShift / contextManager->leds.size())) * 127 + 128;
      contextManager->leds.buffer[i] = {static_cast<uint8_t>(std::floor(phase)), 0, 0};
    }

    gameOverLedPhaseShift += 0.5f;
    if (gameOverLedPhaseShift > contextManager->leds.size())
      gameOverLedPhaseShift = 0;
  }
}