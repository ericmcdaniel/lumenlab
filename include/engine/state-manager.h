#pragma once

#include "games/testing-sandbox/game-state.h"
#include "games/recall/recall-state.h"
#include "scenes/canvas/canvas-state.h"

namespace Engine
{
  enum class SystemState
  {
    Initialize,
    MenuHome,
    MenuGames,
    MenuScenes,
    GameSandbox,
    GameRecall,
    SceneCanvas,
    NoControllerConnected,
    Error
  };

  enum class MainMenuSelection
  {
    Games,
    Scenes,
    COUNT
  };

  enum class GameSelection
  {
    Sandbox,
    Recall,
    PhaseEvasion,
    COUNT
  };

  enum class SceneSelection
  {
    Canvas,
    COUNT
  };

  enum class MenuNavigationDirection
  {
    Forward,
    Reverse
  };

  class StateManager
  {
  public:
    StateManager() : systemState{SystemState::Initialize},
                     userMainMenuChoice{MainMenuSelection::Games},
                     userGameChoice{GameSelection::Sandbox} {}
    bool isRunning() { return systemState != SystemState::Error; }
    bool displayShouldUpdate = true;

    const SystemState current() const { return systemState; }
    void setNext(SystemState state);

    const MainMenuSelection getUserMenuChoice() const { return userMainMenuChoice; }
    void setNextUserMenuChoice(MainMenuSelection next) { userMainMenuChoice = next; };
    void selectNextMenu(MenuNavigationDirection direction = MenuNavigationDirection::Forward);

    const GameSelection getUserGameChoice() const { return userGameChoice; }
    void setNextUserGameChoice(GameSelection next) { userGameChoice = next; };
    void selectNextGame(MenuNavigationDirection direction = MenuNavigationDirection::Forward);

    const SceneSelection getUserSceneChoice() const { return userSceneChoice; }
    void setNextUserSceneChoice(SceneSelection next) { userSceneChoice = next; };
    void selectNextScene(MenuNavigationDirection direction = MenuNavigationDirection::Forward);

    const char *printGameName(uint8_t index);
    const char *printSceneName(uint8_t index);
    Games::SandboxGameState &getSandboxGameState() { return sandboxGameState; }
    Games::RecallGameState &getRecallGameState() { return recallGameState; }
    Scenes::CanvasSceneState &getCanvasSceneState() { return canvasSceneState; }

  private:
    SystemState systemState = SystemState::MenuHome;
    MainMenuSelection userMainMenuChoice = MainMenuSelection::Games;
    GameSelection userGameChoice = GameSelection::Sandbox;
    SceneSelection userSceneChoice = SceneSelection::Canvas;
    Games::SandboxGameState sandboxGameState;
    Games::RecallGameState recallGameState;
    Scenes::CanvasSceneState canvasSceneState;
  };
}