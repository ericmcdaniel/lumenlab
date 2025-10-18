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
    Ambient,
    COUNT
  };

  enum class Games_Selection
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
    MainMenu_Selection userMenuChoice;
    Games_Selection userGameChoice;

  public:
    StateManager() : curr{StateOptions::Initialize}, userMenuChoice{MainMenu_Selection::Games}, userGameChoice{Games_Selection::Sandbox} {}
    StateManager(StateOptions cs) : curr{cs}, userMenuChoice{MainMenu_Selection::Games}, userGameChoice{Games_Selection::Sandbox} {}
    bool isRunning() { return curr != StateOptions::Error; }

    const StateOptions getCurrent() const { return curr; }
    void setNext(StateOptions cs);

    const MainMenu_Selection getUserMenuChoice() const { return userMenuChoice; }
    void setNextUserMenuChoice(MainMenu_Selection next) { userMenuChoice = next; };
    void selectNextMenu(MenuNavigationDirection direction = MenuNavigationDirection::Forward);

    const Games_Selection getUserGameChoice() const { return userGameChoice; }
    void setNextUserGameChoice(Games_Selection next) { userGameChoice = next; };
    void selectNextGame(MenuNavigationDirection direction = MenuNavigationDirection::Forward);
  };
}