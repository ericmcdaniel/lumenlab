#pragma once

#include "engine/system-config.h"
#include "engine/state-manager.h"
#include "engine/timer.h"
#include "lights/led-strip.h"
#include "display/display.h"
#include "games/testing-sandbox/test-core.h"
#include "games/testing-sandbox/test-player.h"

namespace Engine
{
  class GameEngine : Timer
  {
  private:
    Engine::SystemConfig config;
    StateManager state;
    Games::TestCore *game = nullptr;
    Player::Controller controller;
    Lights::LedStrip leds;
    Display::OledDisplay display;

    void initializeEngine();
    void initSandbox();
    void renderLedStrip();

  public:
    GameEngine();

    void runApplication();
    void standbyControllerConnection();
    void navigateMainMenu();
    void navigateGameMenu();
    void checkChangeRequest();
  };
}