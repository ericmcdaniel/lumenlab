#pragma once

#include "engine/layer.h"
#include "engine/timer.h"
#include "core/context-manager.h"

namespace Games
{
  class PhaseEvasionCore : public Engine::Layer, private Engine::Timer
  {
  public:
    PhaseEvasionCore(Core::ContextManager *ctx);
    void nextEvent() override;

  private:
    Core::ContextManager *contextManager;
  };
}