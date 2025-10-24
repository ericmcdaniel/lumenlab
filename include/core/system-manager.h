#pragma once

#include "engine/state-manager.h"
#include "engine/system-config.h"
#include "engine/layer.h"
#include "player/controller.h"
#include "display/display.h"
#include "lights/led-strip.h"

namespace Core
{
  class SystemManager
  {
  private:
    Engine::StateManager &state;
    Engine::SystemConfig &config;

    Player::Controller &controller;
    Display::OledDisplay &display;
    Lights::LedStrip &leds;

  public:
    SystemManager(Engine::SystemConfig &cf, Engine::StateManager &s, Player::Controller &c, Display::OledDisplay &d, Lights::LedStrip &l);
    Engine::Layer *application = nullptr;

    float disconnectedLedPhaseShift = 0;
    void navigateMainMenu();
    void navigateGameMenu();
    void checkChangeRequest();
    void transitionLayer();
  };
}