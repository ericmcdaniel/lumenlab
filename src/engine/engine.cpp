#include <cmath>
#include "engine/engine.h"
#include "games/testing-sandbox/test-player.h"

namespace Engine
{

  GameEngine::GameEngine() : leds{config}, display{controller, state}, systemManager{state, controller, display}
  {
    initializeEngine();
  }

  void GameEngine::runApplication()
  {
    while (state.isRunning())
    {
      if (isReady())
      {
        leds.reset();
        systemManager.checkChangeRequest();
        display.updateDisplay();

        switch (state.getCurrent())
        {
        case SystemState::Menu_Home:
          systemManager.navigateMainMenu();
          break;
        case SystemState::Menu_Games:
          systemManager.navigateGameMenu();
          break;
        case SystemState::Game_SandboxTransition:
          transitionToSandbox();
          break;
        case SystemState::Game_Sandbox:
          game->nextEvent();
          break;
        case SystemState::NoControllerConnected:
          standbyControllerConnection();
          break;
        default:
          // ideally shouldn't encounter this
          state.setNext(SystemState::Error);
          break;
        }

        renderLedStrip();
        wait(9); // Targeting a 120Hz refresh rate. 1/120Hz * 1000 gives us 8.3333ms per frame
      }
    }
  }

  void GameEngine::initializeEngine()
  {
    controller.begin(config.macAddress);

    // If debugging, ensure serial connection is stable before setting up components
#if defined(VIRTUALIZATION) || defined(DEBUG)
    Serial.begin(921600);
    leds.reset();
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
    while (!controller.isConnected() && reattempt < 80)
    {
      log("    Searching for PS3 controller...");
      ++reattempt;
      delay(250);
    }

    if (!controller.isConnected())
    {
      state.setNext(SystemState::NoControllerConnected);
      log("Failed to connect to controller. Entering No Controller Connection sequence until a connection is established.");
    }
    else
    {
      state.setNext(SystemState::Menu_Home);
      log("Startup process completed. Transitioning to Main Menu");
    }
  }

  void GameEngine::standbyControllerConnection()
  {
    if (controller.isConnected())
    {
      state.setNext(SystemState::Menu_Home);
      log("PS3 controller connected. Transitioning to Main Menu");
      return;
    }

    for (int i = 0; i <= leds.size(); ++i)
    {
      float phase = std::cos((2 * M_PI * i / 300) + (2 * M_PI * systemManager.disconnectedLedPhaseShift / 300)) * 127 + 128;
      leds.buffer[i].r = std::floor(phase);
      leds.buffer[i].g = 0;
      leds.buffer[i].b = 0;
    }
    systemManager.disconnectedLedPhaseShift += 0.5;

    if (systemManager.disconnectedLedPhaseShift > 300)
      systemManager.disconnectedLedPhaseShift = 0;
  }

  void GameEngine::transitionToSandbox()
  {
    log("Transitioning to Sandbox game.");
    if (game)
    {
      delete game;
      game = nullptr;
    }
    game = new Games::TestCore{config, state, leds, controller};
    state.getSandboxGameState().reset();
    state.setNext(SystemState::Game_Sandbox);
  }

  void GameEngine::renderLedStrip()
  {
    leds.adjustLuminance();
#ifdef RELEASE
    // TODO: Add actual logic to send signal to LEDs. Below is a simulation only

    ////// do NOT include this in the final build obviously, this is for testing purposes only /////
    Serial.println("LED strip updated.");
    ////////////////////////////////////////////////////////////////////////////////////////////////
#endif
#ifdef VIRTUALIZATION
    Serial.write(0xAA); // sync bytes
    Serial.write(0x55);
    Serial.write(reinterpret_cast<uint8_t *>(leds.getRawColors()), leds.size() * sizeof(CRGB));
#endif
  }
}