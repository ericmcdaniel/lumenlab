#include "engine/state-manager.h"
#include "logger.h"

namespace Engine
{
  void StateManager::setNext(SystemState currentState)
  {
    switch (currentState)
    {
    case SystemState::Game_Sandbox:
      if (systemState != SystemState::Game_SandboxTransition)
      {
        log("Transitioning to Game (Sandbox) (Transition Layer).");
        systemState = SystemState::Game_SandboxTransition;
      }
      else
      {
        log("Transitioning to Game (Sandbox).");
        systemState = currentState;
      }
      break;
    case SystemState::Game_Recall:
      if (systemState != SystemState::Game_RecallTransition)
      {
        log("Transitioning to Game (Recall) (Transition Layer).");
        systemState = SystemState::Game_RecallTransition;
      }
      else
      {
        log("Transitioning to Game (Sandbox).");
        systemState = currentState;
      }
      break;
    default:
      systemState = currentState;
      break;
    }
    displayShouldUpdate = true;
  };

  void StateManager::selectNextMenu(MenuNavigationDirection direction)
  {
    int count = static_cast<int>(MainMenu_Selection::COUNT);
    int position = static_cast<int>(userMainMenuChoice);
    int step = (direction == MenuNavigationDirection::Forward) ? 1 : -1;

    position = (position + step + count) % count;

    userMainMenuChoice = static_cast<MainMenu_Selection>(position);
    displayShouldUpdate = true;
  }

  void StateManager::selectNextGame(MenuNavigationDirection direction)
  {
    int count = static_cast<int>(Game_Selection::COUNT);
    int position = static_cast<int>(userGameChoice);
    int step = (direction == MenuNavigationDirection::Forward) ? 1 : -1;

    position = (position + step + count) % count;

    userGameChoice = static_cast<Game_Selection>(position);
    displayShouldUpdate = true;
  }

  const char *StateManager::printGameName(size_t index)
  {
    static constexpr const char gameNames[3][20] = {
        "Sandbox (Testing)",
        "Recall",
        "Phase Evasion"};
    return gameNames[index];
  }
}