#pragma once

#include "engine/system-config.h"
#include "engine/run-state.h"
#include "engine/timeable.h"
#include "engine/navigation.h"
#include "player/player.h"
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
    Player::Player *player = nullptr;
    Player::GameController controller;
    Lights::LedStrip leds;
    Display::OledDisplay display;

    void handleStartup();
    void initSandbox();
    void render();

  public:
    RunState currentState;

    GameEngine();
    void runApplication();
  };
}