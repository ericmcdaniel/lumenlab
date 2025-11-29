#include <stdlib.h>

#include "games/demo/demo-player.h"

namespace Games
{

  void DemoPlayer::move(const int distance)
  {
    int delta = distance / 20;

    position = (position + delta) % static_cast<int>(contextManager->leds.size());
    if (position < 0)
      position += static_cast<int>(contextManager->leds.size()) - abs(delta);
  }

  void DemoPlayer::updatePlayer1LedBuffer()
  {
    float center = (width + 1) / 2.0f;
    for (uint8_t i = 1; i <= width; ++i)
    {
      size_t index = (position + i) % contextManager->leds.size();
      float intensity = 1.0f - abs(i - center) / center;
      if (intensity < 0)
        intensity = 0;

      contextManager->leds.buffer[index].r = static_cast<uint8_t>(245.0f * intensity);
      contextManager->leds.buffer[index].g = static_cast<uint8_t>(215.0f * intensity);
      contextManager->leds.buffer[index].b = static_cast<uint8_t>(128.0f * intensity);
    }
  }

  void DemoPlayer::updatePlayer2LedBuffer()
  {

    float center = (width + 1) / 2.0f;
    for (uint8_t i = 1; i <= width; ++i)
    {
      size_t index = (position + i) % contextManager->leds.size();
      float intensity = 1.0f - abs(i - center) / center;
      if (intensity < 0)
        intensity = 0;

      contextManager->leds.buffer[index].r = static_cast<uint8_t>(103.0f * intensity);
      contextManager->leds.buffer[index].g = static_cast<uint8_t>(162.0f * intensity);
      contextManager->leds.buffer[index].b = static_cast<uint8_t>(235.0f * intensity);
    }
  }
}