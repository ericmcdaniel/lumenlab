#pragma once

namespace Engine
{
  enum class CoreStateOptions
  {
    INITIALIZE,
    MAIN_MENU,
    NO_CONTROLLER_CONNECTION,
    TRANSITION_SANDBOX,
    GAME_SANDBOX,
    ERROR
  };

  class CoreStateManager
  {
  private:
    CoreStateOptions curr;

  public:
    CoreStateManager() : curr{CoreStateOptions::INITIALIZE} {}
    CoreStateManager(CoreStateOptions cs) : curr{cs} {}
    // ~CoreStateManager() = delete;

    const CoreStateOptions getCurrent() const { return curr; }
    void setNext(CoreStateOptions cs);
    bool isRunning() { return curr != CoreStateOptions::ERROR; }
  };
}