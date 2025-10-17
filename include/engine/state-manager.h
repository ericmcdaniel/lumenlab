#pragma once

namespace Engine
{
  enum class StateOptions
  {
    Initialize,
    MenuHome,
    MenuGames,
    MenuScenes,
    NoControllerConnected,
    TransitionSandbox,
    GameSandbox,
    Error
  };

  class StateManager
  {
  private:
    StateOptions curr;

  public:
    StateManager() : curr{StateOptions::Initialize} {}
    StateManager(StateOptions cs) : curr{cs} {}

    const StateOptions getCurrent() const { return curr; }
    void setNext(StateOptions cs);
    bool isRunning() { return curr != StateOptions::Error; }
  };
}