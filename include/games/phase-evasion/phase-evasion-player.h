#pragma once

#include "core/context-manager.h"
#include "player/player.h"

namespace Games
{
  class PhaseEvasionPlayer : public Player::Player
  {
  public:
    PhaseEvasionPlayer(Core::ContextManager *ctx) : contextManager{ctx}, Player::Player{ctx} {};

  private:
    Core::ContextManager *contextManager;
  };
}