#pragma once

#include "games/testing-sandbox/game-state.h"

namespace Engine
{
  enum class SystemState
  {
    Initialize,
    Menu_Home,
    Menu_Games,
    Menu_Scenes,
    Game_SandboxTransition,
    Game_Sandbox,
    NoControllerConnected,
    Error
  };

  enum class MainMenu_Selection
  {
    Games,
    Scenes,
    COUNT
  };

  enum class Game_Selection
  {
    Sandbox,
    Recall,
    PhaseEvasion,
    COUNT
  };

  enum class MenuNavigationDirection
  {
    Forward,
    Reverse
  };

  class StateManager
  {
  private:
    SystemState systemState;
    MainMenu_Selection userMainMenuChoice;
    Game_Selection userGameChoice;
    Games::SandboxGameState sandboxGameState;

  public:
    StateManager() : systemState{SystemState::Initialize}, userMainMenuChoice{MainMenu_Selection::Games}, userGameChoice{Game_Selection::Sandbox} {}
    bool isRunning() { return systemState != SystemState::Error; }
    bool displayShouldUpdate = true;

    const SystemState getCurrent() const { return systemState; }
    void setNext(SystemState state);

    const MainMenu_Selection getUserMenuChoice() const { return userMainMenuChoice; }
    void setNextUserMenuChoice(MainMenu_Selection next) { userMainMenuChoice = next; };
    void selectNextMenu(MenuNavigationDirection direction = MenuNavigationDirection::Forward);

    const Game_Selection getUserGameChoice() const { return userGameChoice; }
    void setNextUserGameChoice(Game_Selection next) { userGameChoice = next; };
    void selectNextGame(MenuNavigationDirection direction = MenuNavigationDirection::Forward);

    Games::SandboxGameState &getSandboxGameState() { return sandboxGameState; }

    bool operator==(const StateManager &other) const
    {
      return this->systemState == other.systemState;
    }

    bool operator!=(const StateManager &other) const
    {
      return !(*this == other);
    }
  };
}