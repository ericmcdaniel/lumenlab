#include <cmath>
#include "engine/engine.h"
#include "games/testing-sandbox/test-player.h"
#include "games/recall/core.h"

namespace Engine
{

  GameEngine::GameEngine() : Timer{}
  {
    initializeEngine();
  }

  GameEngine::~GameEngine()
  {
    if (contextManager.application)
    {
      delete contextManager.application;
      contextManager.application = nullptr;
    }
  }

  void GameEngine::runApplication()
  {
    while (contextManager.stateManager.isRunning())
    {
      contextManager.leds.reset();

      contextManager.checkChangeRequest();
      contextManager.display.updateDisplay();

      switch (contextManager.stateManager.getCurrent())
      {
      case SystemState::MenuHome:
        contextManager.navigateMainMenu();
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

      if (isReady())
      {
        renderLedStrip();
        wait(9); // Targeting a 120Hz refresh rate. 1/120Hz * 1000 gives us 8.3333ms per frame
      }
      delay(1);
    }
  }

  void GameEngine::initializeEngine()
  {
    contextManager.controller.begin(contextManager.config.macAddress);

    // If debugging, ensure serial connection is stable before setting up components
#if defined(VIRTUALIZATION) || defined(DEBUG)
    Serial.begin(921600);
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

    log("Attempting to connect to PS3 controller");

    // ten second attempt to connect to PS3 controller
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
      log("Startup process completed. Transitioning to Main Menu");
    }
  }

  void GameEngine::standbyControllerConnection()
  {
    if (contextManager.controller.isConnected())
    {
      contextManager.stateManager.setNext(SystemState::MenuHome);
      log("PS3 controller connected. Transitioning to Main Menu");
      return;
    }

    for (int i = 0; i <= contextManager.leds.size(); ++i)
    {
      float phase = std::cos((2 * M_PI * i / 300) + (2 * M_PI * contextManager.disconnectedLedPhaseShift / 300)) * 127 + 128;
      contextManager.leds.buffer[i].r = std::floor(phase);
      contextManager.leds.buffer[i].g = 0;
      contextManager.leds.buffer[i].b = 0;
    }
    contextManager.disconnectedLedPhaseShift += 0.5;

    if (contextManager.disconnectedLedPhaseShift > 300)
      contextManager.disconnectedLedPhaseShift = 0;
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
}