#include <Ps3Controller.h>
#include "player/game-controller.h"

// For referecnce
// // void Player::GameController::update_state()
// // {
// //   // Player::GameController::instance->_data = Ps3.data;
// //   // _data = Ps3.data;
// }

namespace Player
{
  // Following Singleton pattern. Only one instance of the game controller can exist
  GameController *GameController::instance = nullptr;

  void GameController::begin(const char *macAddress)
  {
    // Ps3.attach(&GameController::staticCallback);
    instance->controller.begin(macAddress);
    instance->controller.attachOnConnect(&GameController::onConnect);
  }
}