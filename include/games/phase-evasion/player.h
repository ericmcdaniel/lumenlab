#pragma once

#include "core/context-manager.h"
#include "player/player.h"

namespace Games::PhaseEvasion
{
  class Player : public ::Player::Player
  {
  public:
    Player(SystemCore::ContextManager *ctx) : contextManager{ctx}, ::Player::Player{ctx} {};
    void checkColorChangeRequest();
    Lights::Color getColor() { return currentColor; }
    static constexpr uint16_t width = 10;

  private:
    SystemCore::ContextManager *contextManager;
    Lights::Color currentColor;
    static constexpr ::Player::ControllerButton availableGameplayButtons[] = {
        ::Player::ControllerButton::Cross,
        ::Player::ControllerButton::Square,
        ::Player::ControllerButton::Triangle,
        ::Player::ControllerButton::Circle};
  };
}