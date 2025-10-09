#include "engine/engine.h"
#include "games/testing-sandbox/test-player.h"

namespace Engine
{

  GameEngine::GameEngine() : Time::Timeable{}, currentState(RunState::MAIN_MENU), leds{config, currentState}, display{controller}
  {
    handleStartup();
  }

  void GameEngine::runApplication()
  {
    while (currentState != RunState::ERROR)
    {
      if (isReady())
      {
        display.checkNavMenuChangeRequest();
        leds.setDefault();

        switch (currentState)
        {
        case RunState::MAIN_MENU:
          break;
        case RunState::TRANSITION_SANDBOX:
          initSandbox();
        case RunState::GAME_SANDBOX:
          break;

        default:
          break;
        }
        leds.adjustLuminance();
        // leds.updateColor();
        render();

        // Shooting for 120Hz refresh rate. 1/120Hz * 1000 gives us 8.3333ms per frame
        wait(9);
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
    player = new TestingSandbox::TestPlayer{config, leds};

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
      currentState = Engine::RunState::ERROR;
      log("Failed to connect to controller.");
    }
    else
    {
      currentState = RunState::MAIN_MENU;
      log("Startup process completed.");
    }
  }

  void GameEngine::initSandbox()
  {
    log("Transitioning to Sandbox game. Deleting the player pointer.");
    if (player)
    {
      delete player;
      player = nullptr;
      log("Successfully deleted the player from previous game.");
    }
    player = new TestingSandbox::TestPlayer{config, leds};
    currentState = RunState::GAME_SANDBOX;
  }

  void GameEngine::render()
  {
#ifdef VIRTUALIZATION
    Serial.println("Working?");
    Serial.write(0xAA);
    Serial.write(0x55);
    Serial.write(reinterpret_cast<uint8_t *>(leds.getRawColors()), leds.size() * sizeof(CRGB));
#endif
#ifdef RELEASE
    // TODO: Add actual logic to send signal to LEDs. Below is a simulation only

    ////// do NOT include this in the final game, this is for testing purposes only /////
    Serial.println("LED strip updated.");
    /////////////////////////////////////////////////////////////////////////////////////
#endif
  }
}