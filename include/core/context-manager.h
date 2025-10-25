#pragma once

#include "engine/state-manager.h"
#include "engine/system-config.h"
#include "engine/layer.h"
#include "player/controller.h"
#include "display/display.h"
#include "lights/led-strip.h"

namespace Core
{
  class ContextManager
  {
  public:
    ContextManager();
    Engine::Layer *application = nullptr;
    Engine::StateManager stateManager;
    Engine::SystemConfig config;
    Player::Controller controller;
    Display::OledDisplay display;
    Lights::LedStrip leds;

    float disconnectedLedPhaseShift = 0;
    void navigateMainMenu();
    void navigateGameMenu();
    void checkChangeRequest();
    void transitionLayer();
  };
}