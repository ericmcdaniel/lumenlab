#include "games/chain-reaction/ion.h"
#include "lights/color.h"
#include "core/configuration.h"
#include "common.h"

namespace Games::ChainReaction
{
  Ion::Ion(uint8_t s) : positionFloat{static_cast<float>(SystemCore::Configuration::numLeds())},
                        speed{0.25f}
  {
    colors.reserve(s);
  }

  void Ion::updatePosition()
  {
    positionFloat -= speed;
    // return here to add logic to deactivate when stacked
  }

  void Ion::assignColors()
  {
    for (int i = 0; i < colors.size(); ++i)
    {
      // uint16_t colorIndex = static_cast<uint16_t>(esp_random()) % arraySize(Lights::colorPalette);
      // colors[i] = Lights::colorPalette[colorIndex];
      colors[i] = Lights::colorPalette[i];
    }
  }
}