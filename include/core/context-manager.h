#pragma once

#include "engine/layer.h"
#include "engine/state-manager.h"
#include "engine/system-config.h"
#include "player/controller.h"
#include "lights/led-strip.h"
#include "display/display.h"

namespace Core
{
  class ContextManager
  {
  public:
    ContextManager();
    ~ContextManager();
    ContextManager(ContextManager &&other) = delete;
    ContextManager(const ContextManager &other) = delete;

    Engine::Layer *application = nullptr;
    Engine::StateManager stateManager;
    Engine::SystemConfig config;
    Player::Controller controller;
    Lights::LedStrip leds;
    Display::OledDisplay display;

    void navigateMainMenu();
    void navigateGameMenu();
    void checkChangeRequest();
    void transitionLayer();
  };
}