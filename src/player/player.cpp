#include "player/player.h"

namespace Player
{

  Player::Player(Engine::SystemConfig &configuration,
                 Engine::RunState &state,
                 Lights::LedStrip &leds) : Time::Timeable{},
                                           config{configuration},
                                           leds{leds}
  {
    controller.begin(config.macAddress);
  };

  void Player::processGameController()
  {
    if (controller.cross())
    {
#ifdef DEBUG
      Serial.println("User pressed X");
#endif
      for (int i = 0; i < leds.buffer.size(); i++)
      {
        leds.buffer[i].r = 255;
        leds.buffer[i].g = 255;
        leds.buffer[i].b = 0;
      }
    }
  }
}