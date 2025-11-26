#include "engine/state-manager.h"

namespace Engine
{
  void StateManager::setNext(SystemState currentState)
  {
    systemState = currentState;
    displayShouldUpdate = true;
  };

  void StateManager::selectNextMenu(MenuNavigationDirection direction)
  {
    int count = static_cast<int>(MainMenuSelection::COUNT);
    int position = static_cast<int>(userMainMenuChoice);
    int step = (direction == MenuNavigationDirection::Forward) ? 1 : -1;

    position = (position + step + count) % count;

    userMainMenuChoice = static_cast<MainMenuSelection>(position);
    displayShouldUpdate = true;
  }

  void StateManager::selectNextGame(MenuNavigationDirection direction)
  {
    int count = static_cast<int>(GameSelection::COUNT);
    int position = static_cast<int>(userGameChoice);
    int step = (direction == MenuNavigationDirection::Forward) ? 1 : -1;

    position = (position + step + count) % count;

    userGameChoice = static_cast<GameSelection>(position);
    displayShouldUpdate = true;
  }

  void StateManager::selectNextScene(MenuNavigationDirection direction)
  {
    int count = static_cast<int>(SceneSelection::COUNT);
    int position = static_cast<int>(userSceneChoice);
    int step = (direction == MenuNavigationDirection::Forward) ? 1 : -1;

    position = (position + step + count) % count;

    userSceneChoice = static_cast<SceneSelection>(position);
    displayShouldUpdate = true;
  }

  const char *StateManager::printGameName(uint8_t index)
  {
    static constexpr const char gameNames[3][20] = {
        "Recall",
        "Phase Evasion",
        "Demo"};
    return gameNames[index];
  }

  const char *StateManager::printSceneName(uint8_t index)
  {
    static constexpr const char sceneNames[1][20] = {"Canvas"};
    return sceneNames[index];
  }
}