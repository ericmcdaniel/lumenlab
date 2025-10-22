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

namespace Games
{
  class Recall
  {
  public:
    Recall();

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