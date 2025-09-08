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

  public:
    RunState currentAction;

    GameEngine() : currentAction(RunState::INITIALIZE), player{config, currentAction}, leds(config, currentAction) {}
    void runApplication();
    void handleStartup();
  };
}