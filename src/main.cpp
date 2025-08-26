#include <Arduino.h>
#include "lights/led-strip.h"
#include "engine/engine.h"
#include "engine/system-config.h"
#include "player/player.h"

const Engine::SystemConfig *config;
Engine::GameEngine *engine = nullptr;
Player::Player *player = nullptr;
Lights::LedStrip *strip = nullptr;

uint8_t ledBuffer[300 * 3 + 2];

int frame_count = 0;
int revolution = 0;

void setup()
{
  delay(1000);

  Serial.begin(921600);
  Serial.print("\n\nConnecting to computer for debugging");
  while (!Serial)
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\n");

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

  delay(2000);

  engine = new Engine::GameEngine();
  strip = new Lights::LedStrip(*config);
  player = new Player::Player(*config);

  Serial.print("\n\nConnecting to controller");
  for (int reattempt = 0; reattempt < 10; ++reattempt)
  {
    if (player->controller.isConnected())
      break;
    Serial.print(".");
    delay(500);
  }
  if (!player->controller.isConnected())
  {
    engine->currentAction = Engine::RunState::INVALID;
  }

  Serial.println("\n\nApplication fully initialized.\n");

  while (engine->currentAction != Engine::RunState::INVALID)
  {
    // player.controller.getUpdate();
    if (player->controller.cross())
    {
      Serial.printf("\n\nX is pressed: %u\n", player->controller.cross());
    }
    if (player->controller.square())
    {
      Serial.printf("\n\n[] is pressed: %u\n", player->controller.square());
    }
    if (player->controller.triangle())
    {
      Serial.printf("\n\nA is pressed: %u\n", player->controller.triangle());
    }
    if (player->controller.circle())
    {
      Serial.printf("\n\nO is pressed: %u\n", player->controller.circle());
      engine->currentAction = Engine::RunState::INVALID;
    }

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
