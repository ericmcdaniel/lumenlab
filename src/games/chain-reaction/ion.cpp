#include "games/chain-reaction/ion.h"
#include "lights/color.h"
#include "common.h"

namespace Games::ChainReaction
{
  Ion::Ion(uint8_t cap) : capacity{cap}
  {
    elements.reserve(maxIonElements);
  }

  void Ion::assignColors()
  {
    for (int i = 0; i < capacity; ++i)
    {
      uint16_t colorIndex = static_cast<uint16_t>(esp_random()) % arraySize(Lights::colorPalette);
      elements[i] = Lights::colorPalette[colorIndex];
    }
  }
}