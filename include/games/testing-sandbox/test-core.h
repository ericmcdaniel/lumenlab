#pragma once

#include "games/testing-sandbox/test-player.h"
#include "player/controller.h"

namespace Games
{
  class TestCore
  {
  private:
    Engine::StateManager &engineState;
    Games::SandboxGameState &gameState;
    TestPlayer *player = nullptr;
    TestPlayer *player2 = nullptr;
    Player::Controller controller;
    Lights::LedStrip &leds;

  public:
    TestCore(Engine::SystemConfig &config, Games::SandboxGameState &s, Lights::LedStrip &l, const Player::Controller &c, Engine::StateManager &sm) : gameState{s}, controller(c), leds(l), engineState{sm}
    {
      player = new Games::TestPlayer{config, gameState, leds};
      player2 = new Games::TestPlayer{config, gameState, leds};
    }
    void nextEvent();
    uint16_t getCurrentScore() { return gameState.currentScore; }
    uint16_t getHighScore() { return gameState.highScore; }
    void incrementCurrentScore();
    void incrementHighScore();
  };
}