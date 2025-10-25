#pragma once

#include "engine/system-config.h"
#include "engine/state-manager.h"
#include "engine/timer.h"
#include "engine/layer.h"
#include "core/context-manager.h"
#include "lights/led-strip.h"
#include "display/display.h"
#include "games/testing-sandbox/test-core.h"
#include "games/testing-sandbox/test-player.h"

namespace Engine
{
  class GameEngine : Timer
  {
  private:
    Core::ContextManager contextManager;
    void initializeEngine();
    void renderLedStrip();

  public:
    GameEngine();
    ~GameEngine();

    void runApplication();
    void standbyControllerConnection();
  };
}