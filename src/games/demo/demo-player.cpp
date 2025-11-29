#include <stdlib.h>
#include <cmath>

#include "games/demo/demo-player.h"

namespace Games
{
  void DemoPlayer::move(const int distance)
  {
    if (distance == 0)
      return;

    constexpr float speed = 4.0f;
    float step = contextManager->controller.analogToSpeed(distance, speed);
    positionPrecise += step;

    const float ledCountF = static_cast<float>(contextManager->leds.size());
    positionPrecise = std::fmod(positionPrecise, ledCountF);

    if (positionPrecise < 0.0f)
      positionPrecise += ledCountF;

    position = static_cast<uint16_t>(std::floor(positionPrecise)) % static_cast<uint16_t>(contextManager->leds.size());
  }

  void DemoPlayer::updatePlayer1LedBuffer()
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

  void DemoPlayer::updatePlayer2LedBuffer()
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