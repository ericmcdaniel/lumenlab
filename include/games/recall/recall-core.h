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

namespace Games
{
  class RecallCore : public Engine::Layer, public Engine::Timer
  {
  public:
    RecallCore(Core::ContextManager *ctx);
    void nextEvent();

  private:
    Core::ContextManager *contextManager;
    ActivePlayer activePlayer = ActivePlayer::Computer;
    Engine::Timer colorPlaybackTimer;

    static constexpr unsigned long playbackDurationTotal = 600;
    static constexpr unsigned long playbackDurationIlluminated = 500;
    static constexpr uint16_t maxRound = 1000;

    uint16_t round = 0;
    uint16_t playbackRound = 0;
    CRGB colorPalette[4] = {
        {0, 0, 255},   // ✕ blue
        {255, 255, 0}, // □ yellow
        {0, 255, 0},   // △ green
        {255, 0, 0}};  // ◯ red
    uint16_t gameplayColors[maxRound];

    void setupGameColors();
    void printComputerPlayback();
    void evaluateUserRecall();
    void incrementRound(uint16_t amount = 1);
    bool incorrectButtonWasPressed(Player::ControllerButton correctButton);
    void displayButtonKeypress();
  };
}