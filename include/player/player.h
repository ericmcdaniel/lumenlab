#pragma once

#include "core/context-manager.h"

namespace Player
{
  class Player
  {
  public:
    Player(SystemCore::ContextManager *ctx) : contextManager{ctx} {};
    void move(const int distance, const float speed);
    uint16_t getPosition() { return position; }
    static constexpr ControllerButton availableGameplayButtons[] = {
        ControllerButton::Cross,
        ControllerButton::Square,
        ControllerButton::Triangle,
        ControllerButton::Circle};

  protected:
    SystemCore::ContextManager *contextManager;
    uint16_t position = 0;
    float positionPrecise = 0.0f;
  };

  inline constexpr auto &availableGameplayButtons = Player::Player::availableGameplayButtons;
}