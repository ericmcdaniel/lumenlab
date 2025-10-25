#pragma once

#include "engine/layer.h"
#include "games/testing-sandbox/test-player.h"
#include "player/controller.h"

namespace Games
{
  class TestCore : public Engine::Layer
  {
  private:
    Engine::StateManager &engineState;
    TestPlayer *player1 = nullptr;
    TestPlayer *player2 = nullptr;
    Player::Controller controller;
    Lights::LedStrip &leds;

  public:
    TestCore(Engine::SystemConfig &config, Engine::StateManager &sm, Lights::LedStrip &l, const Player::Controller &c)
        : Engine::Layer{},
          engineState{sm},
          leds{l},
          controller{c}
    {
      player1 = new Games::TestPlayer{config, engineState.getSandboxGameState(), leds};
      player2 = new Games::TestPlayer{config, engineState.getSandboxGameState(), leds};
      engineState.getRecallGameState().reset();
    }

    ~TestCore()
    {
      delete player1;
      delete player2;
    }

    void nextEvent();
    uint16_t getCurrentScore() { return engineState.getSandboxGameState().currentScore; }
    uint16_t getHighScore() { return engineState.getSandboxGameState().highScore; }
    void incrementCurrentScore();
    void incrementHighScore();
  };
}