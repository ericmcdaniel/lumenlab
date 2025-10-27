#pragma once

#include "engine/timer.h"
#include "core/context-manager.h"

namespace Engine
{
  class GameEngine : Timer
  {
  public:
    GameEngine();
    virtual ~GameEngine() = default;
    GameEngine(const GameEngine &) = delete;
    GameEngine &operator=(const GameEngine &) = delete;

    void runApplication();
    void standbyControllerConnection();

  private:
    Core::ContextManager contextManager;
    void initializeEngine();
    void renderLedStrip();
  };
}