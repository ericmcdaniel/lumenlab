#pragma once

#include "engine/state-manager.h"
#include "player/controller.h"
#include "display/display.h"

namespace Core
{
  class SystemManager
  {
  private:
    Engine::StateManager &state;
    Player::Controller &controller;
    Display::OledDisplay &display;

  public:
    SystemManager(Engine::StateManager &s, Player::Controller &c, Display::OledDisplay &d);

    float disconnectedLedPhaseShift = 0;
    void navigateMainMenu();
    void navigateGameMenu();
    void checkChangeRequest();
  };
}