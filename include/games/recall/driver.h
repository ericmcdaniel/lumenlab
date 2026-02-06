#pragma once

#include <cstdint>
#include "core/context-manager.h"
#include "engine/timer.h"
#include "lights/color.h"
#include "lights/color-code.h"
#include "player/player.h"

namespace Games::Recall
{
  class Driver : public Engine::Layer, private Engine::Timer
  {
  public:
    Driver(SystemCore::ContextManager *ctx);
    void nextEvent() override;

  private:
    SystemCore::ContextManager *contextManager;
    GameState &state = contextManager->stateManager.getRecallGameState();

    uint16_t gameplaySpeedIlluminated = 500;
    uint16_t gameplaySpeedPaused = gameplaySpeedIlluminated / 6;
    static constexpr uint16_t maxRound = 1000;
    static constexpr auto &availableGameplayButtons = ::Player::BasePlayer::availableGameplayButtons;
    uint16_t sequenceIndex = 0;
    Player::ControllerButton gameplayColors[maxRound];
    float gameOverLedPhaseShift = 0.0f;
    float successFadeawayAnimation = 1.0f;

    void setupGameColors();
    void handleUserSpeedChange();
    void displayComputerPlayback();
    void pauseComputerPlayback();
    void prepareComputerPlayback();
    void evaluateUserRecall();
    void evaluateUserButton(Player::ControllerButton button);
    void illuminateOnSelection();
    std::pair<uint16_t, uint16_t> directionBoundaries(Player::ControllerButton button);
    void gameOver();
  };
}