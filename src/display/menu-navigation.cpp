#include "display/menu-navigation.h"
#include "engine/state-manager.h"
#include "core/context-manager.h"

namespace Display
{
  void MenuTileNavigation::displayMenuNavigation()
  {
    constexpr uint8_t numModes = static_cast<uint8_t>(Engine::MainMenuSelection::COUNT);
    Engine::MainMenuSelection modeSelected = contextManager->stateManager.getUserMenuChoice();
    Engine::SystemState currentState = contextManager->stateManager.current();

    uint16_t displayIndex = SystemCore::Configuration::numLeds - 1;
    float inactiveSelectionDimmingScale = currentState == Engine::SystemState::MenuHome ? 1.0f : 0.3f;
    constexpr float center = (menuTileWidth - 1) / 2.0f;
    constexpr double sigma = 3.0f;

    for (uint8_t modeIdx = 0; modeIdx < numModes; ++modeIdx)
    {
      for (uint16_t i = 0; i < menuTileWidth; ++i)
      {
        float x = i - center;
        float blend = std::exp(-(x * x) / (2 * sigma * sigma)); // computed gaussian curve

        if (modeIdx == static_cast<uint8_t>(modeSelected))
          contextManager->leds.buffer[displayIndex] = Lights::Color{Lights::ColorCode::ThemeGreen} * inactiveSelectionDimmingScale * blend;
        else
          contextManager->leds.buffer[displayIndex] = Lights::Color{Lights::ColorCode::MenuUnselected} * inactiveSelectionDimmingScale * blend;

        displayIndex--;
      }

      if (modeIdx < numModes - 1)
        displayIndex -= (menuTileWidth / 2);
    }

    constexpr uint8_t numGames = static_cast<uint8_t>(Engine::GameSelection::COUNT);
    uint8_t gameSelected = static_cast<uint8_t>(contextManager->stateManager.getUserGameChoice());

    constexpr uint8_t numScenes = static_cast<uint8_t>(Engine::SceneSelection::COUNT);
    uint8_t sceneSelected = static_cast<uint8_t>(contextManager->stateManager.getUserSceneChoice());

    displayIndex = 0;
    inactiveSelectionDimmingScale = (currentState == Engine::SystemState::MenuGames || currentState == Engine::SystemState::MenuScenes) ? 1.0f : 0.3f;
    uint8_t gamesOrScenesAvailable = modeSelected == Engine::MainMenuSelection::Games ? numGames : numScenes;

    for (uint8_t modeIdx = 0; modeIdx < gamesOrScenesAvailable; ++modeIdx)
    {
      for (size_t i = 0; i < menuTileWidth; ++i)
      {
        float x = i - center;
        float blend = std::exp(-(x * x) / (2 * sigma * sigma));

        if (currentState == Engine::SystemState::MenuGames && modeIdx == gameSelected)
          contextManager->leds.buffer[displayIndex] = Lights::Color{Lights::ColorCode::ThemeBlue} * blend;
        else if (currentState == Engine::SystemState::MenuScenes && modeIdx == sceneSelected)
          contextManager->leds.buffer[displayIndex] = Lights::Color{Lights::ColorCode::ThemeYellow} * blend;
        else
          contextManager->leds.buffer[displayIndex] = Lights::Color{Lights::ColorCode::MenuUnselected} * inactiveSelectionDimmingScale * blend;

        displayIndex++;
      }

      if (modeIdx < gamesOrScenesAvailable - 1)
        displayIndex += (menuTileWidth / 2);
    }
  }
}