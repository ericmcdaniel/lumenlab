#include "player/player.h"

namespace Player
{

  Player::Player(Engine::SystemConfig &configuration,
                 Engine::RunState &state,
                 Lights::LedBuffer &ledBuffer) : Time::Timeable(state),
                                                 config{configuration},
                                                 ledBuffer{ledBuffer}
  {
    controller.begin(config.macAddress);
  };

  void Player::processGameController()
  {
    if (controller.cross())
    {
      for (int i = 0; i < ledBuffer.size(); i++)
      {
        ledBuffer[i].r = 255;
        ledBuffer[i].g = 255;
        ledBuffer[i].b = 0;
      }
    }
  }
}