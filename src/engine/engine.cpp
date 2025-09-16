#include "engine/engine.h"

namespace Engine
{

  GameEngine::GameEngine() : currentAction(RunState::INITIALIZE), player{config, currentAction}, leds(config, currentAction)
  {
    this->handleStartup();
  }

  void GameEngine::runApplication()
  {
    while (this->currentAction != RunState::ERROR)
    {
      switch (this->currentAction)
      {
      case RunState::INITIALIZE:
        // GameEngine::handleStartup();
        break;

      default:
        break;
      }

      leds.updateColor();
      render();
      delay(100);
    }
  }

  void GameEngine::handleStartup()
  {
    Serial.print("\n\nConnecting to controller");

    // ten second attempt to connect to PS3 controller
    int reattempt = 0;
    while (!player.controller.isConnected() || reattempt < 20)
    {
      Serial.print(".");
      ++reattempt;
      delay(500);
    }

    if (!player.controller.isConnected())
    {
      this->currentAction = Engine::RunState::ERROR;
      Serial.println("Failed to connect to controller.");
    }
    else
    {
      this->currentAction = RunState::GAME;
      Serial.println("Startup process completed.");
    }

    delay(1000);
    // display.initialize();
  }

  void GameEngine::render()
  {
    // TODO: Add actual logic to send signal to LEDs. Below is a simulation only

    size_t remaining = leds.getSize() * 3 + 2;
    const uint8_t *ptr = reinterpret_cast<const uint8_t *>(leds.getRawColors());
    Serial.write(0xAA);
    Serial.write(0x55);
    while (remaining > 0)
    {
      size_t n = (remaining > 64) ? 64 : remaining;
      Serial.write(ptr, n);
      // Serial.write(reinterpret_cast<uint8_t *>(leds.getRawColors()), leds.getSize());
      ptr += n;
      remaining -= n;
    }
    // Serial.write(reinterpret_cast<uint8_t *>(leds.getRawColors()), leds.getSize());
  }
}