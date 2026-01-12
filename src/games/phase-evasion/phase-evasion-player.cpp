#include "games/phase-evasion/phase-evasion-player.h"
#include "logger.h"

namespace Games
{
  void PhaseEvasionPlayer::checkColorChangeRequest()
  {
    for (auto button : availableGameplayButtons)
    {
      if (contextManager->controller.isDown(button))
      {
#ifdef DEBUG
        if (currentColor != colorPalette[static_cast<uint16_t>(button)])
        {
          auto c = colorPalette[static_cast<uint16_t>(button)];
          logf("User pressed color=%u (%u - %u - %u)", button, c.r, c.g, c.b);
        }
#endif
        currentColor = colorPalette[static_cast<uint16_t>(button)];
        return;
      }
    }
    if (currentColor != Lights::Color::DimGray)
    {
      log("User returned color to neutral.");
      currentColor = Lights::Color::DimGray;
    }
  }
}