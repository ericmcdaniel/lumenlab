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
    auto leftInput = controller.leftAnalog();
    auto rightInput = controller.rightAnalog();
    player1->move(leftInput.x);
    player1->updatePlayer1LedBuffer();
    player2->move(rightInput.x);
    player2->updatePlayer2LedBuffer();
  }

  void TestCore::incrementCurrentScore()
  {
    ++engineState.getSandboxGameState().currentScore;
    engineState.displayShouldUpdate = true;
  }

  void TestCore::incrementHighScore()
  {
    ++engineState.getSandboxGameState().highScore;
    engineState.displayShouldUpdate = true;
  }
}