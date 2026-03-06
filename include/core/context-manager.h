#pragma once

#include <Preferences.h>

#include "engine/layer.h"
#include "engine/state-manager.h"
#ifdef USE_PS3
#include "player/ps3-controller.h"
#else
#include "player/ps4-controller.h"
#endif
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
#ifdef USE_PS3
    Player::Ps3Controller controller;
#else
    Player::Ps4Controller controller;
#endif
    Lights::LedStrip leds;
    Display::OledDisplay display;
    Preferences memory;
    Display::MenuTileNavigation menuNav;

    void initializeSystemMemory();
    void navigateMainMenu();
    void navigateGameMenu();
    void navigateSceneMenu();
    void checkExitRequest();
    void checkDisplayVisibilityChange();
    void transitionLayer();
  };
}