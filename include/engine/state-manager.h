#pragma once

#include "games/recall/recall-state.h"
#include "games/phase-evasion/phase-evasion-state.h"
#include "games/demo/demo-state.h"
#include "scenes/canvas/canvas-state.h"

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
    StateManager() : systemState{SystemState::Initialize},
                     userMainMenuChoice{MainMenuSelection::Games},
                     userGameChoice{GameSelection::Recall} {}
    bool isRunning() { return systemState != SystemState::Error; }
    bool displayShouldUpdate = true;
    bool displayIsVisible = true;
    uint32_t displayDebounce = millis();
    uint32_t debounceThreshold = 200;

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

    Games::RecallGameState &getRecallGameState() { return recallGameState; }
    Games::PhaseEvasionGameState &getPhaseEvasionGameState() { return phaseEvasionGameState; }
    Games::DemoGameState &getDemoGameState() { return demoGameState; }

    Scenes::CanvasSceneState &getCanvasSceneState() { return canvasSceneState; }

  private:
    SystemState systemState = SystemState::MenuHome;

    MainMenuSelection userMainMenuChoice = MainMenuSelection::Games;
    GameSelection userGameChoice = GameSelection::Demo;
    SceneSelection userSceneChoice = SceneSelection::Canvas;

    Games::RecallGameState recallGameState;
    Games::PhaseEvasionGameState phaseEvasionGameState;
    Games::DemoGameState demoGameState;

    Scenes::CanvasSceneState canvasSceneState;
  };
}