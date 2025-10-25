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
  class RecallCore : public Engine::Layer, public Engine::Timer
  {
  public:
    RecallCore(Engine::StateManager &sm, Lights::LedStrip &l, const Player::Controller &c);
    void nextEvent();

  private:
    Engine::StateManager &engineState;
    Player::Controller controller;
    Lights::LedStrip &leds;

    uint8_t round = 0;
    CRGB colorPalette[4] = {
        {255, 0, 0},
        {0, 255, 0},
        {0, 0, 255},
        {255, 255, 0}};
    CRGB gameplayColors[256];

    uint8_t playbackRound = 0;
    void setupGameColors();
  };
}