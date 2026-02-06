#pragma once

#include "core/context-manager.h"

namespace Player
{
  class BasePlayer
  {
  public:
    BasePlayer(SystemCore::ContextManager *ctx, const uint16_t w) : contextManager{ctx}, width{w} {};

    const uint16_t width;

    void move(const int distance, const float speed, const bool shouldWrap = true);

    uint16_t getPosition() { return static_cast<uint16_t>(positionPrecise); }
    void setPosition(float position) { positionPrecise = position; }
    void setPosition(uint16_t position) { positionPrecise = static_cast<float>(position); }

    float analogToSpeed(int value, float maxOutput) const;

    static constexpr ControllerButton availableGameplayButtons[] = {
        ControllerButton::Cross,
        ControllerButton::Square,
        ControllerButton::Triangle,
        ControllerButton::Circle};

  protected:
    SystemCore::ContextManager *contextManager;
    float positionPrecise = 0.0f;
    float responseExponent = 2.0f;
    float responseBlend = 0.35f;
  };

  inline constexpr auto &availableGameplayButtons = BasePlayer::BasePlayer::availableGameplayButtons;
}