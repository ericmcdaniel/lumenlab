#pragma once

#include "core/context-manager.h"

namespace Engine
{
  class GameEngine
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
    uint32_t lastRender = 0;
    void initializeEngine();
    void renderLedStrip();
    void displayMainMenuSelection();
    void displayGameSelection();
    static void displayTask(void *param);
    float disconnectedLedPhaseShift = 0;
  };
}