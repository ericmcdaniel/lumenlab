#include "engine/engine.h"

namespace Engine
{

  GameEngine::GameEngine() : currentAction(RunState::MENU), leds{config, currentAction}, player{config, currentAction, leds}
  {
    handleStartup();
  }

  void GameEngine::runApplication()
  {
    while (currentAction != RunState::ERROR)
    {
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
      delay(15);
    }
  }

  void GameEngine::handleStartup()
  {
    delay(500);

    // Ensure engine is stable before setting up components
    Serial.begin(921600);
    Serial.print("\n\nConnecting to computer for debugging");
    while (!Serial)
    {
      Serial.print(".");
      delay(100);
    }
    Serial.println("\n");

    delay(1000);
    Serial.print("\n\nConnecting to controller");

    // ten second attempt to connect to PS3 controller
    int reattempt = 0;
    while (!player.controller.isConnected() && reattempt < 20)
    {
      Serial.print(".");
      ++reattempt;
      delay(500);
    }

    if (!player.controller.isConnected())
    {
      currentAction = Engine::RunState::ERROR;
      Serial.println("Failed to connect to controller.");
    }
    else
    {
      currentAction = RunState::GAME;
      Serial.println("Startup process completed.");
    }

    delay(1000);
    // display.initialize();
  }

  void GameEngine::render()
  {
    // TODO: Add actual logic to send signal to LEDs. Below is a simulation only

    Serial.write(0xAA);
    Serial.write(0x55);
    Serial.write(reinterpret_cast<uint8_t *>(leds.getRawColors()), leds.getSize());
  }
}