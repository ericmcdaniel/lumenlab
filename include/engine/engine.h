#pragma once

#include "engine/system-config.h"
#include "player/player.h"
#include "lights/led-strip.h"

namespace Engine
{
  enum class RunState
  {
    INITIALIZE,
    GAME,
    INVALID
  };

  class GameEngine
  {
  private:
    Engine::SystemConfig config;
    Player::Player player;
    Lights::LedStrip leds;

  public:
    RunState currentAction;

    GameEngine() : player{config}, leds{config}, currentAction(RunState::INITIALIZE) {}
    void runApplication();
    void handleStartup();
  };
}