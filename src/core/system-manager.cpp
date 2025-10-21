#include "core/system-manager.h"

namespace Core
{
  SystemManager::SystemManager(Engine::StateManager &s, Player::Controller &c, Display::OledDisplay &d) : state{s}, controller{c}, display{d} {}

  void SystemManager::checkChangeRequest()
  {
    if (controller.wasPressed(Player::ControllerButton::Ps))
    {
      state.setNext(Engine::SystemState::Menu_Home);
      log("Transitioning to Main Menu.");
    }
  }

  void SystemManager::navigateMainMenu()
  {
    if (controller.wasPressed(Player::ControllerButton::Down))
    {
      state.selectNextMenu();
      logf("Highlighting Main Menu option %d", state.getUserMenuChoice());
    }

    if (controller.wasPressed(Player::ControllerButton::Up))
    {
      state.selectNextMenu(Engine::MenuNavigationDirection::Reverse);
      logf("Highlighting Main Menu option %d", state.getUserMenuChoice());
    }

    if (controller.wasPressed(Player::ControllerButton::Start) || controller.wasPressed(Player::ControllerButton::Cross))
    {
      switch (state.getUserMenuChoice())
      {
      case Engine::MainMenu_Selection::Games:
        state.setNext(Engine::SystemState::Menu_Games);
        log("Transitioning to Game Submenu.");
        break;
      case Engine::MainMenu_Selection::Scenes:
        break;
      }
    }
  }

  void SystemManager::navigateGameMenu()
  {
    if (controller.wasPressed(Player::ControllerButton::Down))
    {
      state.selectNextGame();
      logf("Highlighting Games Submenu option %s", state.printGameName(static_cast<int>(state.getUserGameChoice())));
    }

    if (controller.wasPressed(Player::ControllerButton::Up))
    {
      state.selectNextGame(Engine::MenuNavigationDirection::Reverse);
      logf("Highlighting Games Submenu option %s", state.printGameName(static_cast<int>(state.getUserGameChoice())));
    }

    if (controller.wasPressed(Player::ControllerButton::Start) || controller.wasPressed(Player::ControllerButton::Cross))
    {
      switch (state.getUserGameChoice())
      {
      case Engine::Game_Selection::Sandbox:
        state.setNext(Engine::SystemState::Game_Sandbox);
        break;
      case Engine::Game_Selection::Recall:
        break;
      }
    }

    if (controller.wasPressed(Player::ControllerButton::Circle))
    {
      state.setNext(Engine::SystemState::Menu_Home);
      log("Transitioning to Main Menu.");
    }
  }

}