#include <cmath>

#include "engine/engine.h"
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
      contextManager.checkChangeRequest();

      switch (contextManager.stateManager.current())
      {
      case SystemState::MenuHome:
        contextManager.navigateMainMenu();
        displayMainMenuSelection();
        break;
      case SystemState::MenuGames:
        contextManager.navigateGameMenu();
        break;
      case SystemState::GameSandbox:
      case SystemState::GameRecall:
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
      lastRender = micros();
      log("Startup process completed. Transitioning to Main Menu");
    }
  }

  void GameEngine::standbyControllerConnection()
  {
    if (contextManager.controller.isConnected())
    {
      contextManager.stateManager.setNext(SystemState::MenuHome);
      lastRender = micros();
      log("PS3 controller connected. Transitioning to Main Menu");
      return;
    }

    for (int i = 0; i <= contextManager.leds.size(); ++i)
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
    uint8_t numOfSupportedModes = static_cast<uint8_t>(MainMenuSelection::COUNT);
    uint8_t option = static_cast<uint8_t>(contextManager.stateManager.getUserMenuChoice());
    uint16_t boundaryWidth = contextManager.leds.size() / numOfSupportedModes;
    uint16_t boundaryStart = boundaryWidth * option;
    uint16_t boundaryEnd = boundaryWidth * (option + 1);
    for (uint16_t i = boundaryStart; i < boundaryEnd; ++i)
    {
      contextManager.leds.buffer[i] = {16, 64, 16};
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
    Serial.write(reinterpret_cast<uint8_t *>(contextManager.leds.getRawColors()), contextManager.leds.size() * sizeof(CRGB));
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