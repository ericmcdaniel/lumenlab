#pragma once

#include "player/game-controller.h"
#include "engine/timeable.h"
#include "engine/system-config.h"
#include "lights/led-buffer.h"

namespace Player
{
  class Player : public Time::Timeable
  {
  private:
    const Engine::SystemConfig &config;
    Lights::LedBuffer &ledBuffer;

  public:
    GameController controller;
    Player(Engine::SystemConfig &configuration, Engine::RunState &state, Lights::LedBuffer &ledBuffer);
    void processGameController();
  };
}