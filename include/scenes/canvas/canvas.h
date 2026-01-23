#pragma once

#include "core/context-manager.h"
#include "engine/timer.h"
#include "lights/color-hsl.h"

namespace Scenes
{
  class Canvas : public Engine::Layer, private Engine::Timer
  {
  public:
    Canvas(SystemCore::ContextManager *ctx);
    void nextEvent() override;

  private:
    SystemCore::ContextManager *contextManager;
    CanvasSceneState &state = contextManager->stateManager.getCanvasSceneState();
    Lights::ColorHsl colorHsl;
    bool hasChange = false;
    bool controllerWasActive = false;

    inline void checkAnalogColorChange();
    inline void checkBalanceColorRequest();
    inline void checkNewColorRequest();
    inline void checkStableControllerForDisplay();
    inline void checkChangeOccured();
    inline void reset();
  };
}