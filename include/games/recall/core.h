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
#include "logger.h"

namespace Games
{
  class RecallCore : public Engine::Layer
  {
  public:
    RecallCore();
    void nextEvent() override
    {
      logf("RecallCore - next event.");
    };

  private:
    uint8_t round = 0;
    CRGB colorPalette[4] = {
        {255, 0, 0},
        {0, 255, 0},
        {0, 0, 255},
        {255, 255, 0}};
    CRGB gameplayColors[256];

    void setupGameColors();
  };
}