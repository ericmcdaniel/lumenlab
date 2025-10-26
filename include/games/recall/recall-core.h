#pragma once

#ifdef RELEASE
#define FASTLED_INTERNAL
#include <FastLED.h>
#undef min
#undef max
#else
#include "debug-fastled.h"
#endif

#include <Ps3Controller.h> // Needed only for the uint8_t definition

#include "engine/layer.h"
#include "engine/timer.h"
#include "player/controller.h"
#include "lights/led-strip.h"
#include "logger.h"

namespace Games
{
  enum class ActivePlayer
  {
    Computer,
    Player
  };

  class RecallCore : public Engine::Layer, public Engine::Timer
  {
  public:
    RecallCore(Engine::StateManager &sm, Lights::LedStrip &l, const Player::Controller &c);
    void nextEvent();

  private:
    Engine::StateManager &engineState;
    Player::Controller controller;
    Lights::LedStrip &leds;
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
    bool shouldDisplayTimedColor = true;

    void setupGameColors();
    void printComputerPlayback();
  };
}