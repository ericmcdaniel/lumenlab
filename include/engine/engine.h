#pragma once

#include "core/context-manager.h"

namespace Engine
{
  class GameEngine
  {
  public:
    GameEngine();

    void runApplication();
    void standbyControllerConnection();

  private:
    SystemCore::ContextManager contextManager;
    uint32_t lastRender = 0;
    float disconnectedLedPhaseShift = 0;
    static constexpr uint16_t menuTileWidth = 12;

    void initializeEngine();
    void renderLedStrip();
    void displayMenuNavigation();
    void displayMainMenuSelection();
    void displayGameSelection();
    void displaySceneSelection();
    static void displayTask(void *param);
  };
}