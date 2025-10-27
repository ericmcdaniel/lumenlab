#include "games/testing-sandbox/test-core.h"
#include "player/controller.h"
#include "logger.h"

namespace Games
{
  void TestCore::nextEvent()
  {
    if (contextManager->controller.wasPressed(Player::ControllerButton::Cross))
    {
      incrementCurrentScore();
      contextManager->stateManager.displayShouldUpdate = true;
      logf("Current score: %d", getCurrentScore());
    }
    auto leftInput = contextManager->controller.leftAnalog();
    auto rightInput = contextManager->controller.rightAnalog();
    player1->move(leftInput.x);
    player1->updatePlayer1LedBuffer();
    player2->move(rightInput.x);
    player2->updatePlayer2LedBuffer();
  }

  void TestCore::incrementCurrentScore()
  {
    ++contextManager->stateManager.getSandboxGameState().currentScore;
    contextManager->stateManager.displayShouldUpdate = true;
  }

  void TestCore::incrementHighScore()
  {
    ++contextManager->stateManager.getSandboxGameState().highScore;
    contextManager->stateManager.displayShouldUpdate = true;
  }
}