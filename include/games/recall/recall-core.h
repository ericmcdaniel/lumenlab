#pragma once

#include <cstdint>

#ifdef RELEASE
#define FASTLED_INTERNAL
#include <FastLED.h>
#undef min
#undef max
#else
#include "debug-fastled.h"
#endif

#include "core/context-manager.h"
#include "engine/timer.h"
#include "lights/color.h"

namespace Games
{
  class RecallCore : public Engine::Layer, private Engine::Timer
  {
  public:
    RecallCore(Core::ContextManager *ctx);
    void nextEvent();

  private:
    Core::ContextManager *contextManager;
    RecallGameState &state = contextManager->stateManager.getRecallGameState();

    static constexpr unsigned long playbackDurationIlluminated = 600;
    static constexpr unsigned long playbackDurationPaused = 100;
    static constexpr uint16_t maxRound = 1000;
    static constexpr Player::ControllerButton availableGameplayButtons[] = {
        Player::ControllerButton::Cross,
        Player::ControllerButton::Square,
        Player::ControllerButton::Triangle,
        Player::ControllerButton::Circle};
    uint16_t sequenceIndex = 0;
    Lights::Color colorPalette[4] = {
        {0, 0, 255},    // ✕ blue
        {255, 0, 0},    // ◯ red
        {0, 255, 0},    // △ green
        {255, 255, 0}}; // □ yellow
    Player::ControllerButton gameplayColors[maxRound];
    float gameOverLedPhaseShift = 0;
    float successFadeawayAnimation = 1;

    void setupGameColors();
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