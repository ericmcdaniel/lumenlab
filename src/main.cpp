#include <Arduino.h>
// #include <Ps3Controller.h>

#include "lights/LedStrip.h"
#include "engine/Engine.h"
#include "player/Player.h"
#include "Exception.h"

// Engine::Engine engine;
// Player::Player player;

uint8_t ledBuffer[300 * 3 + 2];

int frame_count = 0;
int revolution = 0;

void setup()
{
  delay(1000);

  // if (engine.currentAction == Engine::State::GAME)
  // {
  //   throw InvalidStateException("Test exception handling.");
  // }

  Serial.begin(921600);
  Serial.print("Connecting.");
  while (!Serial)
  {
    Serial.print(".");
    delay(100);
  }

  ledBuffer[0] = 0xAA;
  ledBuffer[1] = 0x55;
  for (int i = 0; i < 300; i++)
  {
    int base = i * 3 + 2;
    ledBuffer[base + 0] = 36;
    ledBuffer[base + 1] = 0;
    ledBuffer[base + 2] = 255;
  }

  Serial.write(ledBuffer, sizeof(ledBuffer));
  Serial.flush();
  delay(1000);

  pinMode(BUILTIN_LED, OUTPUT);
  Serial.println("\nUSB LED data sender ready.");

  // Engine::Engine engine;
  Player::Player player{};

  Serial.println("Ready.");
  Lights::LedStrip strip{300};

  while (true)
  {
    // player.controller.getUpdate();
    if (player.controller.cross())
      Serial.println("\n\nX is pressed.");
    if (player.controller.square())
      Serial.println("\n\n[] is pressed.");
    if (player.controller.triangle())
      Serial.println("\n\nA is pressed.");
    if (player.controller.circle())
      Serial.println("\n\nO is pressed.");

    ledBuffer[0] = 0xAA;
    ledBuffer[1] = 0x55;
    for (int i = 0; i < 300; i++)
    {
      int base = i * 3 + 2;
      ledBuffer[base + 0] = 36;
      ledBuffer[base + 1] = 200;
      ledBuffer[base + 2] = 36;
    }

    Serial.write(ledBuffer, sizeof(ledBuffer));
    Serial.flush();
    delay(1000);

    for (int i = 0; i < 300; i++)
    {
      int base = i * 3 + 2;
      ledBuffer[base + 0] = 0;
      ledBuffer[base + 1] = 0;
      ledBuffer[base + 2] = 0;
    }

    Serial.write(ledBuffer, sizeof(ledBuffer));
    Serial.flush();
    delay(1000);
  }
}

/**
 * loop() functions just as a catch block does in modern
 * try/catch exception handling. There is no game logic
 * here, only the strip oscillating on and off in red.
 */
void loop()
{
  ledBuffer[0] = 0xAA;
  ledBuffer[1] = 0x55;
  for (int i = 0; i < 300; i++)
  {
    int base = i * 3 + 2;
    ledBuffer[base + 0] = 255;
    ledBuffer[base + 1] = 0;
    ledBuffer[base + 2] = 0;
  }

  Serial.write(ledBuffer, sizeof(ledBuffer));
  Serial.flush();
  delay(500);

  for (int i = 0; i < 300; i++)
  {
    int base = i * 3 + 2;
    ledBuffer[base + 0] = 0;
    ledBuffer[base + 1] = 0;
    ledBuffer[base + 2] = 0;
  }

  Serial.write(ledBuffer, sizeof(ledBuffer));
  Serial.flush();
  delay(500);

  // // First two bytes are sync markers
  // ledBuffer[0] = 0xAA;
  // ledBuffer[1] = 0x55;

  // // Fill LED buffer
  // for (int i = 0; i < 300; i++)
  // {
  //   int base = i * 3 + 2;
  //   if (abs(i - frame_count) <= 2)
  //   {
  //     ledBuffer[base + 0] = 255; // R
  //     ledBuffer[base + 1] = 0;   // G
  //     ledBuffer[base + 2] = 0;   // B
  //     // Serial.printf("frame_count is: %d.\n", frame_count);
  //   }
  //   // else if (frame_count % 100 == 0 || controller.triangle())
  //   // {
  //   //   ledBuffer[base + 0] = 0;   // R
  //   //   ledBuffer[base + 1] = 255; // G
  //   //   ledBuffer[base + 2] = 0;   // B
  //   // }
  //   // else if (frame_count % 100 == 0 || controller.square())
  //   // {
  //   //   ledBuffer[base + 0] = 255; // R
  //   //   ledBuffer[base + 1] = 255; // G
  //   //   ledBuffer[base + 2] = 0;   // B
  //   // }
  //   // else if (frame_count % 100 == 0)
  //   // {
  //   //   ledBuffer[base + 0] = 0;   // R
  //   //   ledBuffer[base + 1] = 0;   // G
  //   //   ledBuffer[base + 2] = 255; // B
  //   // }

  //   else
  //   {
  //     ledBuffer[base + 0] = 0;
  //     ledBuffer[base + 1] = 0;
  //     ledBuffer[base + 2] = 0;
  //     // Serial.printf("Count is: %d.\tPrinting Black.\n", count);
  //   }
  // }
  // if (controller.cross())
  //   frame_count = (frame_count + 8) % 300;
  // else if (controller.square())
  //   frame_count = (frame_count + 1) % 300;
  // else if (controller.triangle())
  //   frame_count = (frame_count + 4) % 300;
  // else if (controller.circle())
  // {
  //   // pass;
  // }
  // else
  //   frame_count = (frame_count + 2) % 300;

  // // Send LED buffer over USB Serial
  // Serial.write(ledBuffer, sizeof(ledBuffer));
  // Serial.flush(); // Ensure data is pushed out
  // delay(10);
}
