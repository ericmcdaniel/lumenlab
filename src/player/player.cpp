#include "player/player.h"

namespace Player
{
  void Player::move(const int distance, const float speed)
  {
    if (distance == 0)
      return;

    float step = contextManager->controller.analogToSpeed(distance, speed);
    positionPrecise += step;

    const float ledCountF = static_cast<float>(contextManager->leds.size());
    positionPrecise = std::fmod(positionPrecise, ledCountF);

    if (positionPrecise < 0.0f)
      positionPrecise += ledCountF;

    position = static_cast<uint16_t>(std::floor(positionPrecise)) % static_cast<uint16_t>(contextManager->leds.size());
  }
}