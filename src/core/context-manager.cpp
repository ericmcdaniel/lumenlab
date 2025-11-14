#include "core/context-manager.h"
#include "games/testing-sandbox/test-core.h"
#include "games/recall/recall-core.h"
#include "logger.h"

namespace Core
{
  ContextManager::ContextManager() : leds{config}, display{this} {}

  ContextManager::~ContextManager()
  {
    if (application)
    {
      delete application;
      application = nullptr;
    }
  }

  void ContextManager::checkChangeRequest()
  {
    if (controller.wasPressed(Player::ControllerButton::Ps))
    {
      stateManager.setNext(Engine::SystemState::MenuHome);
      stateManager.setNextUserMenuChoice(Engine::MainMenuSelection::Games);
      stateManager.setNextUserGameChoice(Engine::GameSelection::Sandbox);
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

    if (controller.wasPressed(Player::ControllerButton::Cross))
    {
      switch (stateManager.getUserMenuChoice())
      {
      case Engine::MainMenuSelection::Games:
        stateManager.setNext(Engine::SystemState::MenuGames);
        log("Transitioning to Game Submenu.");
        break;
      case Engine::MainMenuSelection::Scenes:
        stateManager.setNext(Engine::SystemState::MenuScenes);
        log("Transitioning to Scenes Submenu.");
        break;
      }
    }
    logf("Main Menu: %d", stateManager.getUserMenuChoice());
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

    if (controller.wasPressed(Player::ControllerButton::Cross))
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

  void ContextManager::navigateSceneMenu()
  {
    if (controller.wasPressed(Player::ControllerButton::Down))
    {
      stateManager.selectNextScene();
      logf("Highlighting Scene Submenu option %s", stateManager.printSceneName(static_cast<int>(stateManager.getUserSceneChoice())));
    }

    if (controller.wasPressed(Player::ControllerButton::Up))
    {
      stateManager.selectNextScene(Engine::MenuNavigationDirection::Reverse);
      logf("Highlighting Scene Submenu option %s", stateManager.printSceneName(static_cast<int>(stateManager.getUserSceneChoice())));
    }

    if (controller.wasPressed(Player::ControllerButton::Cross))
    {
      switch (stateManager.getUserSceneChoice())
      {
      case Engine::SceneSelection::Canvas:
        stateManager.setNext(Engine::SystemState::SceneCanvas);
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
    switch (stateManager.current())
    {
    case Engine::SystemState::GameSandbox:
      application = new Games::TestCore{this};
      logf("Transitioning to Sandbox (Testing)");
      break;
    case Engine::SystemState::GameRecall:
      application = new Games::RecallCore{this};
      logf("Transitioning to Recall (Game)");
      break;
    case Engine::SystemState::SceneCanvas:
      // application = new Games::RecallCore{this};
      logf("Transitioning to Canvas (Scene)");
      break;
    }
  }

}