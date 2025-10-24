#include "core/system-manager.h"
#include "games/testing-sandbox/test-core.h"
#include "games/recall/core.h"
#include "logger.h"

namespace Core
{
  SystemManager::SystemManager(Engine::SystemConfig &cf,
                               Engine::StateManager &s,
                               Player::Controller &c,
                               Display::OledDisplay &d,
                               Lights::LedStrip &l)
      : config{cf}, state{s}, controller{c}, display{d}, leds{l} {}

  void SystemManager::checkChangeRequest()
  {
    if (controller.wasPressed(Player::ControllerButton::Ps))
    {
      state.setNext(Engine::SystemState::MenuHome);
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
      case Engine::MainMenuSelection::Games:
        state.setNext(Engine::SystemState::MenuGames);
        log("Transitioning to Game Submenu.");
        break;
      case Engine::MainMenuSelection::Scenes:
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
      case Engine::GameSelection::Sandbox:
        state.setNext(Engine::SystemState::GameSandbox);
        break;
      case Engine::GameSelection::Recall:
        state.setNext(Engine::SystemState::GameRecall);
        break;
      }
      transitionLayer();
    }

    if (controller.wasPressed(Player::ControllerButton::Circle))
    {
      state.setNext(Engine::SystemState::MenuHome);
      log("Transitioning to Main Menu.");
    }
  }

  void SystemManager::transitionLayer()
  {
    if (application)
    {
      delete application;
      application = nullptr;
    }
    switch (state.getCurrent())
    {
    case Engine::SystemState::GameSandbox:
      application = new Games::TestCore{config, state, leds, controller};
      state.getSandboxGameState().reset();
      logf("Transitioning to Sandbox (Testing)");
      break;
    case Engine::SystemState::GameRecall:
      application = new Games::RecallCore{};
      logf("Transitioning to Recall (Game)");
      break;
    }
  }

}