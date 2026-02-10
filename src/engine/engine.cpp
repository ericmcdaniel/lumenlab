#include <cmath>

#include <FastLED.h>
#include <Preferences.h>
#include "engine/engine.h"
#include "lights/color.h"
#include "display/menu-navigation.h"
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
        break;
      case SystemState::MenuGames:
        contextManager.navigateGameMenu();
        break;
      case SystemState::MenuScenes:
        contextManager.navigateSceneMenu();
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
    contextManager.controller.begin(SystemCore::Configuration::macAddress);

// If debugging, ensure serial connection is stable before setting up components
#if defined(VIRTUALIZATION) || defined(DEBUG)
    Serial.begin(SystemCore::Configuration::serialBaud);
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

#ifdef RELEASE
    contextManager.memory.begin("lumenlab", false);
#else
    contextManager.memory.begin("lumenlab-development", false);
#endif

    randomSeed(esp_random());
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

    for (uint16_t i = 0; i <= SystemCore::Configuration::numLeds; ++i)
    {
      float phase = std::cos((2 * M_PI * i / SystemCore::Configuration::numLeds) + (2 * M_PI * disconnectedLedPhaseShift / SystemCore::Configuration::numLeds)) * 127 + 128;
      contextManager.leds.buffer[i] = {static_cast<uint8_t>(std::floor(phase)), 0, 0};
    }
    disconnectedLedPhaseShift += 0.5;

    if (disconnectedLedPhaseShift > SystemCore::Configuration::numLeds)
      disconnectedLedPhaseShift = 0;
  }

  void GameEngine::renderLedStrip()
  {
    contextManager.leds.adjustLuminance();
#ifdef RELEASE
    FastLED.show();
#endif
#ifdef VIRTUALIZATION
    Serial.write(0xAA); // sync bytes
    Serial.write(0x55);
    Serial.write(reinterpret_cast<uint8_t *>(contextManager.leds.getRawColors()), SystemCore::Configuration::numLeds * sizeof(Lights::Color));
#endif
  }

  void GameEngine::displayTask(void *param)
  {
    auto *ctx = static_cast<SystemCore::ContextManager *>(param);
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