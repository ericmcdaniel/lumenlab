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
    ///
  }
}