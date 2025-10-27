#pragma once

#include "core/context-manager.h"

namespace Player
{
  class Player
  {
  public:
    Player(Core::ContextManager *ctx) : contextManager{ctx} {};

  private:
    Core::ContextManager *contextManager;
  };
}