#pragma once

#include "engine/layer.h"
#include "engine/state-manager.h"
#include "player/controller.h"
#include "lights/led-strip.h"
#include "display/display.h"
#include "display/menu-navigation.h"

namespace SystemCore
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
    Player::Controller controller;
    Lights::LedStrip leds;
    Display::OledDisplay display;
    Display::MenuTileNavigation menuNav;

    void navigateMainMenu();
    void navigateGameMenu();
    void navigateSceneMenu();
    void checkExitRequest();
    void checkDisplayVisibilityChange();
    void transitionLayer();
  };
}