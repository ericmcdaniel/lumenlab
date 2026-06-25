#pragma once

#include "core/context-manager.h"
#include "player/player.h"

namespace Games::Reflex
{
  class Signal : public ::Player::BasePlayer
  {
  public:
    Signal(SystemCore::ContextManager *ctx, uint16_t width, float _speed);
    ~Signal() = default;

    void advance() { setPosition(positionPrecise += speed); }

  private:
    float speed;
  };
}
