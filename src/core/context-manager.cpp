#include "core/context-manager.h"
#include "games/testing-sandbox/test-core.h"
#include "games/recall/recall-core.h"
#include "logger.h"

namespace Core
{
  ContextManager::ContextManager() : leds{config},
                                     display{controller, stateManager} {}

  void ContextManager::checkChangeRequest()
  {
    if (controller.wasPressed(Player::ControllerButton::Ps))
    {
      stateManager.setNext(Engine::SystemState::MenuHome);
      log("Transitioning to Main Menu.");
    }
  }

  void ContextManager::navigateMainMenu()
  {
    if (controller.wasPressed(Player::ControllerButton::Down))
    {
      stateManager.selectNextMenu();
      logf("Highlighting Main Menu option %d", stateManager.getUserMenuChoice());
    }

    if (controller.wasPressed(Player::ControllerButton::Up))
    {
      stateManager.selectNextMenu(Engine::MenuNavigationDirection::Reverse);
      logf("Highlighting Main Menu option %d", stateManager.getUserMenuChoice());
    }

    if (controller.wasPressed(Player::ControllerButton::Start) || controller.wasPressed(Player::ControllerButton::Cross))
    {
      switch (stateManager.getUserMenuChoice())
      {
      case Engine::MainMenuSelection::Games:
        stateManager.setNext(Engine::SystemState::MenuGames);
        log("Transitioning to Game Submenu.");
        break;
      case Engine::MainMenuSelection::Scenes:
        break;
      }
    }
  }

  void ContextManager::navigateGameMenu()
  {
    if (controller.wasPressed(Player::ControllerButton::Down))
    {
      stateManager.selectNextGame();
      logf("Highlighting Games Submenu option %s", stateManager.printGameName(static_cast<int>(stateManager.getUserGameChoice())));
    }

    if (controller.wasPressed(Player::ControllerButton::Up))
    {
      stateManager.selectNextGame(Engine::MenuNavigationDirection::Reverse);
      logf("Highlighting Games Submenu option %s", stateManager.printGameName(static_cast<int>(stateManager.getUserGameChoice())));
    }

    if (controller.wasPressed(Player::ControllerButton::Start) || controller.wasPressed(Player::ControllerButton::Cross))
    {
      switch (stateManager.getUserGameChoice())
      {
      case Engine::GameSelection::Sandbox:
        stateManager.setNext(Engine::SystemState::GameSandbox);
        break;
      case Engine::GameSelection::Recall:
        stateManager.setNext(Engine::SystemState::GameRecall);
        break;
      }
      transitionLayer();
    }

    if (controller.wasPressed(Player::ControllerButton::Circle))
    {
      stateManager.setNext(Engine::SystemState::MenuHome);
      log("Transitioning to Main Menu.");
    }
  }

  void ContextManager::transitionLayer()
  {
    if (application)
    {
      delete application;
      application = nullptr;
    }
    switch (stateManager.getCurrent())
    {
    case Engine::SystemState::GameSandbox:
      application = new Games::TestCore{this};
      logf("Transitioning to Sandbox (Testing)");
      break;
    case Engine::SystemState::GameRecall:
      application = new Games::RecallCore{this};
      logf("Transitioning to Recall (Game)");
      break;
    }
  }

}