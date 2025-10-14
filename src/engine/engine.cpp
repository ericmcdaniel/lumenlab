#include "engine/engine.h"
#include "games/testing-sandbox/test-player.h"

namespace Engine
{

  GameEngine::GameEngine() : currentState(RunState::MAIN_MENU), leds{config}, navigation{currentState, controller}
  {
    handleStartup();
  }

  void GameEngine::runApplication()
  {
    while (currentState != RunState::ERROR)
    {
      if (refreshRateTimer.isReady())
      {
        leds.reset();

        switch (currentState)
        {
        case RunState::MAIN_MENU:
          // moving directly to the TestingSandbox game for testing
          currentState = RunState::TRANSITION_SANDBOX;
          break;
        case RunState::TRANSITION_SANDBOX:
          initSandbox();
          break;
        case RunState::GAME_SANDBOX:
          game->nextEvent();
          break;
        case RunState::NO_CONTROLLER_CONNECTION:
          standbyControllerConnection();
          break;
        default:
          // ideally shouldn't encounter this
          currentState = RunState::ERROR;
          break;
        }

        renderLedStrip();
        refreshRateTimer.wait(9); // Shooting for 120Hz refresh rate. 1/120Hz * 1000 gives us 8.3333ms per frame
      }
    }
  }

  void GameEngine::handleStartup()
  {
    controller.begin(config.macAddress);

    // If debugging, ensure serial connection is stable before setting up components
#if defined(VIRTUALIZATION) || defined(DEBUG)
    Serial.begin(921600);
    log("Connecting to computer using a serial connection for debugging.");
    while (!Serial)
    {
      log("    No Serial connection...");
      delay(100);
    }
    log("Serial connection established.");
#endif

    log("Attempting to connect to PS3 controller");
    game = new Games::TestCore{config, leds, controller};

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
      currentState = Engine::RunState::NO_CONTROLLER_CONNECTION;
      log("Failed to connect to controller.");
    }
    else
    {
      currentState = RunState::MAIN_MENU;
      log("Startup process completed.");
    }
  }

  void GameEngine::standbyControllerConnection()
  {
    while (!controller.isConnected())
    {
      for (int i = 0; i <= leds.size(); ++i)
      {
        leds.buffer[i].r = 255;
        leds.buffer[i].g = 0;
        leds.buffer[i].b = 0;
      }
    }
  }

  void GameEngine::initSandbox()
  {
    log("Transitioning to Sandbox game.");
    if (game)
    {
      delete game;
      game = nullptr;
    }
    game = new Games::TestCore{config, leds, controller};
    currentState = RunState::GAME_SANDBOX;
  }

  void GameEngine::renderLedStrip()
  {
    leds.adjustLuminance();
#ifdef VIRTUALIZATION
    Serial.write(0xAA); // sync bytes
    Serial.write(0x55);
    Serial.write(reinterpret_cast<uint8_t *>(leds.getRawColors()), leds.size() * sizeof(CRGB));
#endif
#ifdef RELEASE
    // TODO: Add actual logic to send signal to LEDs. Below is a simulation only

    ////// do NOT include this in the final build obviously, this is for testing purposes only /////
    Serial.println("LED strip updated.");
    ////////////////////////////////////////////////////////////////////////////////////////////////
#endif
  }
}