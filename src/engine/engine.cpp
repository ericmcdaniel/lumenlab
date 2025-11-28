#include <cmath>

#include "engine/engine.h"
#include "lights/color.h"
#include "logger.h"

namespace Engine
{
  GameEngine::GameEngine()
  {
    initializeEngine();
    xTaskCreatePinnedToCore(
        GameEngine::displayTask,
        "OLED Display Task",
        4096,
        &contextManager,
        1,
        nullptr,
        0);
  }

  void GameEngine::runApplication()
  {
    while (contextManager.stateManager.isRunning())
    {
      contextManager.leds.reset();
      contextManager.controller.poll();
      contextManager.checkExitRequest();
      contextManager.checkDisplayVisibilityChange();

      switch (contextManager.stateManager.current())
      {
      case SystemState::MenuHome:
        contextManager.navigateMainMenu();
        displayMainMenuSelection();
        break;
      case SystemState::MenuGames:
        contextManager.navigateGameMenu();
        displayGameSelection();
        break;
      case SystemState::MenuScenes:
        contextManager.navigateSceneMenu();
        displaySceneSelection();
        break;
      case SystemState::GameRecall:
      case SystemState::GamePhaseEvasion:
      case SystemState::GameDemo:
      case SystemState::SceneCanvas:
        contextManager.application->nextEvent();
        break;
      case SystemState::NoControllerConnected:
        standbyControllerConnection();
        break;
      default:
        // ideally shouldn't encounter this
        contextManager.stateManager.setNext(SystemState::Error);
        break;
      }

      uint32_t now = micros();
      if (now - lastRender >= 8333) // Targeting a 120Hz refresh rate. 1/120Hz * 1000 gives us 8.3333ms per frame
      {
        lastRender += 8333;
        renderLedStrip();
      }
    }
  }

  void GameEngine::initializeEngine()
  {
    contextManager.controller.begin(contextManager.config.macAddress);

    // If debugging, ensure serial connection is stable before setting up components
#if defined(VIRTUALIZATION) || defined(DEBUG)
    Serial.begin(contextManager.config.serialBaud);
    contextManager.leds.reset();
    renderLedStrip();
    log("Connecting to computer using a serial connection for debugging.");
    while (!Serial)
    {
      log("    No Serial connection...");
      delay(100);
    }
    log("Serial connection established.");
#endif

    log("Connecting to PS3 controller");

    // twenty second attempt to connect to PS3 controller
    int reattempt = 0;
    while (!contextManager.controller.isConnected() && reattempt < 80)
    {
      log("    Searching for PS3 controller...");
      ++reattempt;
      delay(250);
    }

    if (!contextManager.controller.isConnected())
    {
      contextManager.stateManager.setNext(SystemState::NoControllerConnected);
      log("Failed to connect to controller. Entering No Controller Connection sequence until a connection is established.");
    }
    else
    {
      contextManager.stateManager.setNext(SystemState::MenuHome);
      contextManager.stateManager.displayIsVisible = true;
      contextManager.controller.reset();
      contextManager.controller.poll();
      lastRender = micros();
      log("Startup process completed. Transitioning to Main Menu");
    }
  }

  void GameEngine::standbyControllerConnection()
  {
    if (contextManager.controller.isConnected())
    {
      contextManager.stateManager.setNext(SystemState::MenuHome);
      contextManager.stateManager.setNextUserMenuChoice(MainMenuSelection::Games);
      contextManager.stateManager.setNextUserGameChoice(GameSelection::Recall);
      contextManager.stateManager.setNextUserSceneChoice(SceneSelection::Canvas);
      lastRender = micros();
      contextManager.stateManager.displayIsVisible = true;
      log("PS3 controller connected. Transitioning to Main Menu");
      return;
    }

    for (uint16_t i = 0; i <= contextManager.leds.size(); ++i)
    {
      float phase = std::cos((2 * M_PI * i / contextManager.leds.size()) + (2 * M_PI * disconnectedLedPhaseShift / contextManager.leds.size())) * 127 + 128;
      contextManager.leds.buffer[i] = {static_cast<uint8_t>(std::floor(phase)), 0, 0};
    }
    disconnectedLedPhaseShift += 0.5;

    if (disconnectedLedPhaseShift > contextManager.leds.size())
      disconnectedLedPhaseShift = 0;
  }

  void GameEngine::displayMainMenuSelection()
  {
    constexpr uint8_t numOfSupportedModes = static_cast<uint8_t>(MainMenuSelection::COUNT);
    uint8_t option = static_cast<uint8_t>(contextManager.stateManager.getUserMenuChoice());
    uint16_t boundaryWidth = contextManager.leds.size() / numOfSupportedModes;
    uint16_t boundaryStart = boundaryWidth * option;
    uint16_t boundaryEnd = boundaryWidth * (option + 1);
    double mu = (boundaryStart + boundaryEnd) / 2.0;
    constexpr double sigma = 35.0;

    for (uint16_t i = boundaryStart; i < boundaryEnd; ++i)
    {
      double x = static_cast<double>(i);
      double scope = std::exp(-0.5 * std::pow((x - mu) / sigma, 2.0));
      contextManager.leds.buffer[i] = Lights::Color{Lights::ColorCode::LightGreen} * scope;
    }
  }

  void GameEngine::displayGameSelection()
  {
    constexpr uint8_t numOfSupportedModes = static_cast<uint8_t>(GameSelection::COUNT);
    uint8_t option = static_cast<uint8_t>(contextManager.stateManager.getUserGameChoice());
    uint16_t boundaryWidth = contextManager.leds.size() / numOfSupportedModes;
    uint16_t boundaryStart = boundaryWidth * option;
    uint16_t boundaryEnd = boundaryWidth * (option + 1);
    double mu = (boundaryStart + boundaryEnd) / 2.0;
    constexpr double sigma = 20.0;

    for (uint16_t i = boundaryStart; i < boundaryEnd; ++i)
    {
      double x = static_cast<double>(i);
      double scope = 100 * std::exp(-0.5 * std::pow((x - mu) / sigma, 2.0));
      contextManager.leds.buffer[i] = Lights::Color{Lights::ColorCode::LightBlue} * (scope / 100.0);
    }
  }

  void GameEngine::displaySceneSelection()
  {
    constexpr uint8_t numOfSupportedModes = static_cast<uint8_t>(SceneSelection::COUNT);
    uint8_t option = static_cast<uint8_t>(contextManager.stateManager.getUserSceneChoice());
    uint16_t boundaryWidth = contextManager.leds.size() / numOfSupportedModes;
    uint16_t boundaryStart = boundaryWidth * option;
    uint16_t boundaryEnd = boundaryWidth * (option + 1);
    double mu = (boundaryStart + boundaryEnd) / 2.0;
    constexpr double sigma = 20.0;

    for (uint16_t i = boundaryStart; i < boundaryEnd; ++i)
    {
      double x = static_cast<double>(i);
      double scope = 100 * std::exp(-0.5 * std::pow((x - mu) / sigma, 2.0));
      contextManager.leds.buffer[i] = Lights::Color{Lights::ColorCode::LightBlue} * (scope / 100.0);
    }
  }

  void GameEngine::renderLedStrip()
  {
    contextManager.leds.adjustLuminance();
#ifdef RELEASE
    // TODO: Add actual logic to send signal to LEDs. Below is a simulation only

    ////// do NOT include this in the final build obviously, this is for testing purposes only /////
    Serial.println("LED strip updated.");
    ////////////////////////////////////////////////////////////////////////////////////////////////
#endif
#ifdef VIRTUALIZATION
    Serial.write(0xAA); // sync bytes
    Serial.write(0x55);
    Serial.write(reinterpret_cast<uint8_t *>(contextManager.leds.getRawColors()), contextManager.leds.size() * sizeof(Lights::Color));
#endif
  }

  void GameEngine::displayTask(void *param)
  {
    auto *ctx = static_cast<Core::ContextManager *>(param);
    while (true)
    {
      if (ctx->stateManager.displayShouldUpdate)
      {
        ctx->display.updateDisplay();
      }
      vTaskDelay(1);
    }
  }
}