#include "player/player.h"

namespace Player
{
  void Player::move(const int distance, const float speed, const bool shouldWrap)
  {
    if (distance == 0)
      return;

    float step = contextManager->controller.analogToSpeed(distance, speed);
    positionPrecise += step;

    const float adjustedLedCount = static_cast<float>(contextManager->leds.size() - width);
    if (shouldWrap)
    {
      positionPrecise = std::fmod(positionPrecise, adjustedLedCount);

      if (positionPrecise < 0.0f)
      {
        positionPrecise += adjustedLedCount;
      }
    }
    else
    {
      if (positionPrecise >= adjustedLedCount)
      {
        positionPrecise = adjustedLedCount;
      }
      else if (positionPrecise < 0.0f)
      {
        positionPrecise = 0.0f;
      }
    }
  }
}