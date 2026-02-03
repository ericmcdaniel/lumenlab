#include "games/phase-evasion/player.h"
#include "logger.h"

namespace Games::PhaseEvasion
{
  void Player::checkColorChangeRequest()
  {
    for (auto button : Player::availableGameplayButtons)
    {
      if (contextManager->controller.isDown(button))
      {
#ifdef DEBUG
        if (currentColor != Lights::colorPalette[static_cast<uint16_t>(button)])
        {
          auto c = Lights::colorPalette[static_cast<uint16_t>(button)];
          logf("User pressed color=%u (%u - %u - %u)", button, c.r, c.g, c.b);
        }
#endif
        currentColor = Lights::colorPalette[static_cast<uint16_t>(button)];
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