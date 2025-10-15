#pragma once

namespace Display
{
  enum class StateOptions
  {
    BootScreen,
    MenuHome,
    MenuGames,
    MenuScenes
  };

  class StateManager
  {
  private:
    StateOptions curr;

  public:
    StateManager() : curr{StateOptions::BootScreen} {}
    StateManager(StateOptions c) : curr{c} {}

    const StateOptions getCurrent() const { return curr; }
    void setNext(StateOptions cs) { curr = cs; }
  };
}