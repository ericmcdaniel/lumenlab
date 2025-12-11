#pragma once

#include "core/context-manager.h"

namespace Player
{
  class Player
  {
  public:
    Player(Core::ContextManager *ctx) : contextManager{ctx} {};
    void move(const int distance, const float speed);
    uint16_t getPosition() { return position; }

  protected:
    Core::ContextManager *contextManager;
    uint16_t position = 0;
    float positionPrecise = 0.0f;
  };
}