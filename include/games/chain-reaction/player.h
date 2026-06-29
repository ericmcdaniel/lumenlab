#pragma once

#include "platform/context-manager.h"
#include "player/player.h"

namespace Games::ChainReaction
{
  class Player
  {
  public:
    Player(SystemCore::ContextManager *ctx) {};
    void checkAccelerator();

    // void checkColorChangeRequest();

  private:
  };
}