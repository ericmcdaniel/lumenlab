#include "esp_system.h"

#include "games/recall/controller.h"
#include "logger.h"

namespace Games
{
  Recall::Recall()
  {
    setupGameColors();
  }

  void Recall::setupGameColors()
  {
    for (size_t i = 0; i < 256; ++i)
    {
      auto colorIndex = esp_random() % 4;
      gameplayColors[i] = colorPalette[colorIndex];
    }
    logf("Setup game colors for Recall.");
    logf("First ten: %d-%d-%d-%d-%d-%d-%d-%d-%d-%d", gameplayColors[0], gameplayColors[1], gameplayColors[2], gameplayColors[3], gameplayColors[4], gameplayColors[5], gameplayColors[6], gameplayColors[7], gameplayColors[8], gameplayColors[9]);
  }
}