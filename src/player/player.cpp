#include "player/player.h"

namespace Player
{
  void BasePlayer::move(const int distance, const float speed, const bool shouldWrap)
  {
    if (distance == 0)
      return;

    float step = analogToSpeed(distance, speed);
    positionPrecise += step;

    const float adjustedLedCount = static_cast<float>(SystemCore::Configuration::numLeds - width);
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

  float BasePlayer::analogToSpeed(int value, float maxOutput) const
  {
    if (value == 0)
      return 0.0f;

    float normalizedAnalogValue = static_cast<float>(value) / 127.0f;
    float sign = (normalizedAnalogValue > 0.0f) ? 1.0f : -1.0f;
    float absoluteValueNormalized = std::abs(normalizedAnalogValue);

    float nonlinear = std::pow(absoluteValueNormalized, responseExponent);
    float mixed = (1.0f - responseBlend) * nonlinear + responseBlend * absoluteValueNormalized;
    float scaled = mixed * maxOutput;
    return sign * scaled;
  }
}