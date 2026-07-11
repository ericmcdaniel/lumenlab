#include "games/chain-reaction/ion.h"
#include "lights/color.h"
#include "platform/configuration.h"
#include "common.h"

namespace Games::ChainReaction
{
  Ion::Ion(uint8_t s) : positionFloat{static_cast<float>(SystemCore::Configuration::numLeds())},
                        speed{0.40f}
  {
    colors.reserve(s);
    assignColors(s);
  }

  void Ion::updatePosition()
  {
    positionFloat -= speed;
    // return here to add logic to deactivate when stacked
  }

  void Ion::assignColors(uint8_t s)
  {
    for (uint8_t i = 0; i < s; ++i)
    {
      // uint16_t colorIndex = static_cast<uint16_t>(esp_random()) % arraySize(Lights::colorPalette);
      // colors.push_back(Lights::colorPalette[colorIndex]);
      colors.push_back(Lights::colorPalette[i]);
    }
  }
}