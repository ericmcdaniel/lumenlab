#pragma once

#include "core/context-manager.h"

namespace Player
{
  class Player
  {
  public:
    Player(SystemCore::ContextManager *ctx, const uint16_t w) : contextManager{ctx}, width{w} {};

    const uint16_t width;

    void move(const int distance, const float speed, const bool shouldWrap = true);
    uint16_t getPosition() { return static_cast<uint16_t>(positionPrecise); }

    static constexpr ControllerButton availableGameplayButtons[] = {
        ControllerButton::Cross,
        ControllerButton::Square,
        ControllerButton::Triangle,
        ControllerButton::Circle};

  protected:
    SystemCore::ContextManager *contextManager;
    float positionPrecise = 0.0f;
  };

  inline constexpr auto &availableGameplayButtons = Player::Player::availableGameplayButtons;
}