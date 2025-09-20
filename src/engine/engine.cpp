#include "engine/engine.h"

namespace Engine
{

  GameEngine::GameEngine() : Time::Timeable{}, currentAction(RunState::MENU), leds{config, currentAction}, player{config, currentAction, leds}
  {
    handleStartup();
  }

  void GameEngine::runApplication()
  {
    while (currentAction != RunState::ERROR)
    {
      if (isReady())
      {

        leds.setDefault();

        switch (currentAction)
        {
        case RunState::MENU:
        case RunState::GAME:
          break;

        default:
          break;
        }

        player.processGameController();
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

    // ten second attempt to connect to PS3 controller
    int reattempt = 0;
    while (!player.controller.isConnected() && reattempt < 80)
    {
      log("    Searching for PS3 controller...");
      ++reattempt;
      delay(250);
    }

    if (!player.controller.isConnected())
    {
      currentAction = Engine::RunState::ERROR;
      log("Failed to connect to controller.");
    }
    else
    {
      currentAction = RunState::GAME;
      log("Startup process completed.");
    }

    // display.initialize();
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
    Serial.println("LED strip updated.");
#endif
  }
}