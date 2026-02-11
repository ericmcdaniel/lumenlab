#pragma once

#include "games/recall/state.h"
#include "games/phase-evasion/state.h"
#include "games/demo/state.h"
#include "scenes/canvas/state.h"

namespace SystemCore
{
  // forward declaration because of ContextManager/OledDisplay circular dependency
  class ContextManager;
}

namespace Engine
{
  enum class SystemState
  {
    Initialize,
    MenuHome,
    MenuGames,
    MenuScenes,
    GameRecall,
    GamePhaseEvasion,
    GameDemo,
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
    Recall,
    PhaseEvasion,
    Demo,
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
    StateManager(SystemCore::ContextManager *ctx) : contextManager{ctx},
                                                    phaseEvasionGameState{ctx},
                                                    recallGameState{ctx},
                                                    systemState{SystemState::Initialize},
                                                    userMainMenuChoice{MainMenuSelection::Games},
                                                    userGameChoice{GameSelection::Recall}
    {
    }

    bool displayShouldUpdate = true;
    bool displayIsVisible = true;

    bool isRunning() const { return systemState != SystemState::Error; }

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

    Games::Recall::GameState &getRecallGameState() { return recallGameState; }
    Games::PhaseEvasion::GameState &getPhaseEvasionGameState() { return phaseEvasionGameState; }
    Games::Demo::GameState &getDemoGameState() { return demoGameState; }

    Scenes::Canvas::SceneState &getCanvasSceneState() { return canvasSceneState; }

  private:
    SystemCore::ContextManager *contextManager;
    SystemState systemState;

    MainMenuSelection userMainMenuChoice;
    GameSelection userGameChoice;
    SceneSelection userSceneChoice;

    Games::Recall::GameState recallGameState;
    Games::PhaseEvasion::GameState phaseEvasionGameState;
    Games::Demo::GameState demoGameState;

    Scenes::Canvas::SceneState canvasSceneState;
  };
}