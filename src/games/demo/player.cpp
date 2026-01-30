#include <stdlib.h>
#include <cmath>

#include "games/demo/player.h"

namespace Games::Demo
{
  void Player::updatePlayer1LedBuffer()
  {
    float center = (width + 1) / 2.0f;
    for (uint16_t i = 1; i <= width; ++i)
    {
      uint16_t index = (position + i) % contextManager->leds.size();
      float intensity = 1.0f - std::abs(i - center) / center;
      if (intensity < 0)
        intensity = 0;

      contextManager->leds.buffer[index].r = static_cast<uint16_t>(245.0f * intensity);
      contextManager->leds.buffer[index].g = static_cast<uint16_t>(215.0f * intensity);
      contextManager->leds.buffer[index].b = static_cast<uint16_t>(128.0f * intensity);
    }
  }

  void Player::updatePlayer2LedBuffer()
  {

    float center = (width + 1) / 2.0f;
    for (uint16_t i = 1; i <= width; ++i)
    {
      uint16_t index = (position + i) % contextManager->leds.size();
      float intensity = 1.0f - std::abs(i - center) / center;
      if (intensity < 0)
        intensity = 0;

      contextManager->leds.buffer[index].r = static_cast<uint16_t>(103.0f * intensity);
      contextManager->leds.buffer[index].g = static_cast<uint16_t>(162.0f * intensity);
      contextManager->leds.buffer[index].b = static_cast<uint16_t>(235.0f * intensity);
    }
  }
}