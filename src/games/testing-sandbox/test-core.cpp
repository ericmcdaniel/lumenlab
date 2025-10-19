#include "games/testing-sandbox/test-core.h"
#include "player/controller.h"
#include "logger.h"

namespace Games
{
  void TestCore::nextEvent()
  {
    if (controller.wasPressed(Player::ControllerButton::Cross))
    {
      incrementCurrentScore();
      engineState.displayShouldUpdate = true;
      logf("Current score: %d", getCurrentScore());
    }
    auto input = controller.leftAnalog();
    auto input2 = controller.rightAnalog();
    player->move(input.x);
    player->updateLedBuffer();
    player2->move(input2.x);
    player2->updateLedBuffer2();
  }

  void TestCore::incrementCurrentScore()
  {
    ++gameState.currentScore;
    engineState.displayShouldUpdate = true;
  }

  void TestCore::incrementHighScore()
  {
    ++gameState.highScore;
    engineState.displayShouldUpdate = true;
  }
}