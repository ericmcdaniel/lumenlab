#pragma once

namespace Engine
{
  enum class StateOptions
  {
    Initialize,
    Menu_Home,
    Menu_Games,
    Menu_Scenes,
    Menu_Ambient,
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
    StateOptions curr;
    MainMenu_Selection userMainMenuChoice;
    Game_Selection userGameChoice;

  public:
    StateManager() : curr{StateOptions::Initialize}, userMainMenuChoice{MainMenu_Selection::Games}, userGameChoice{Game_Selection::Sandbox} {}
    StateManager(StateOptions cs) : curr{cs}, userMainMenuChoice{MainMenu_Selection::Games}, userGameChoice{Game_Selection::Sandbox} {}
    bool isRunning() { return curr != StateOptions::Error; }

    const StateOptions getCurrent() const { return curr; }
    void setNext(StateOptions cs);

    const MainMenu_Selection getUserMenuChoice() const { return userMainMenuChoice; }
    void setNextUserMenuChoice(MainMenu_Selection next) { userMainMenuChoice = next; };
    void selectNextMenu(MenuNavigationDirection direction = MenuNavigationDirection::Forward);

    const Game_Selection getUserGameChoice() const { return userGameChoice; }
    void setNextUserGameChoice(Game_Selection next) { userGameChoice = next; };
    void selectNextGame(MenuNavigationDirection direction = MenuNavigationDirection::Forward);

    bool operator==(const StateManager &other) const
    {
      return this->curr == other.curr;
    }

    bool operator!=(const StateManager &other) const
    {
      return !(*this == other);
    }
  };
}