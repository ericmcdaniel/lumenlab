#include <Ps3Controller.h>
#include "player/controller.h"

// For referecnce
// // void Player::Controller::update_state()
// // {
// //   // Player::Controller::instance->_data = Ps3.data;
// //   // this->_data = Ps3.data;
// }

namespace Player
{
  // Following Singleton pattern. Only one instance of the game controller can exist
  Controller *Controller::instance = nullptr;

  void Controller::begin(const char *macAddress)
  {
    // Ps3.attach(&Controller::staticCallback);
    instance->controller.begin(macAddress);
    instance->controller.attachOnConnect(&Controller::onConnect);
  }
}