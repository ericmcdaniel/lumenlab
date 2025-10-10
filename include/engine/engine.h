#pragma once

#include "engine/system-config.h"
#include "engine/run-state.h"
#include "engine/timeable.h"
#include "engine/navigation.h"
#include "games/testing-sandbox/test-core.h"
#include "lights/led-strip.h"
#include "display/display.h"
#include "games/testing-sandbox/test-player.h"

namespace Engine
{
  class GameEngine : private Time::Timeable
  {
  private:
    Engine::SystemConfig config;
    Engine::Navigation navigation;
    Games::TestCore *game = nullptr;
    Player::Controller controller;
    Lights::LedStrip leds;
    Display::OledDisplay display;

    void handleStartup();
    void initSandbox();
    void renderLedStrip();

  public:
    RunState currentState;

    GameEngine();
    void runApplication();
  };
}