#include <Arduino.h>
#include "lights/led-strip.h"
#include "engine/engine.h"
#include "engine/system-config.h"
#include "player/player.h"

void setup()
{
  Engine::GameEngine engine;
  engine.runApplication();
}

/**
 * loop() functions just as a catch block does in modern try/catch exception handling.
 * There is no game logic here, only the strip oscillating on and off in red.
 */
void loop()
{
  Serial.println("LumenLab has encountered an error state.");
  delay(1000);
}
