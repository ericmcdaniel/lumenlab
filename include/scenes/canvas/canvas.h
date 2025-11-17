#pragma once

#include "core/context-manager.h"
#include "engine/timer.h"

namespace Scenes
{
  class Canvas : public Engine::Layer, private Engine::Timer
  {
  public:
    Canvas(Core::ContextManager *ctx) : contextManager{ctx} {};
    void nextEvent();

  private:
    Core::ContextManager *contextManager;
    CanvasSceneState &state = contextManager->stateManager.getCanvasSceneState();
    void checkColorChange();
  };
}