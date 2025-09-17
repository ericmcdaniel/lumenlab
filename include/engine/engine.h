#pragma once

#include "engine/system-config.h"
#include "engine/run-state.h"
#include "player/player.h"
#include "lights/led-strip.h"
#include "display/display.h"

namespace Engine
{
  class GameEngine
  {
  private:
    Engine::SystemConfig config;
    Player::Player player;
    Lights::LedStrip leds;
    Display::OledDisplay display;

    void handleStartup();
    void render();

  public:
    RunState currentAction;

    GameEngine();
    void runApplication();
  };
}