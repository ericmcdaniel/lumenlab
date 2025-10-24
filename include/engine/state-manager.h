#pragma once

#include "games/testing-sandbox/game-state.h"

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

  enum class MenuNavigationDirection
  {
    Forward,
    Reverse
  };

  class StateManager
  {
  private:
    SystemState systemState;
    MainMenuSelection userMainMenuChoice;
    GameSelection userGameChoice;
    Games::SandboxGameState sandboxGameState;

  public:
    StateManager() : systemState{SystemState::Initialize},
                     userMainMenuChoice{MainMenuSelection::Games},
                     userGameChoice{GameSelection::Sandbox} {}
    bool isRunning() { return systemState != SystemState::Error; }
    bool displayShouldUpdate = true;

    const SystemState getCurrent() const { return systemState; }
    void setNext(SystemState state);

    const MainMenuSelection getUserMenuChoice() const { return userMainMenuChoice; }
    void setNextUserMenuChoice(MainMenuSelection next) { userMainMenuChoice = next; };
    void selectNextMenu(MenuNavigationDirection direction = MenuNavigationDirection::Forward);

    const GameSelection getUserGameChoice() const { return userGameChoice; }
    void setNextUserGameChoice(GameSelection next) { userGameChoice = next; };
    void selectNextGame(MenuNavigationDirection direction = MenuNavigationDirection::Forward);

    Games::SandboxGameState &getSandboxGameState() { return sandboxGameState; }
    const char *printGameName(size_t index);

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