#pragma once

#include "core/context-manager.h"
#include "engine/timer.h"
#include "lights/color-hsl.h"

namespace Scenes::Canvas
{
  class Controller : public Engine::Layer, private Engine::Timer
  {
  public:
    Controller(SystemCore::ContextManager *ctx);
    void nextEvent() override;

  private:
    SystemCore::ContextManager *contextManager;
    SceneState &state = contextManager->stateManager.getCanvasSceneState();
    Lights::ColorHsl colorHsl;
    bool hasChange = false;
    bool controllerWasActive = false;

    void checkAnalogColorChange();
    void checkBalanceColorRequest();
    void checkNewColorRequest();
    void checkStableControllerForDisplay();
    void checkChangeOccured();
    void reset();
  };
}