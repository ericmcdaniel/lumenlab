#include "games/demo/controller.h"
#include "player/controller.h"
#include "logger.h"

namespace Games::Demo
{
  void Controller::nextEvent()
  {
    if (contextManager->controller.wasPressed(::Player::ControllerButton::Cross))
    {
      incrementCurrentScore();
      contextManager->stateManager.displayShouldUpdate = true;
      logf("Current score: %d", getCurrentScore());
    }
    auto leftInput = contextManager->controller.leftAnalog();
    auto rightInput = contextManager->controller.rightAnalog();
    player1.move(leftInput.x, speed);
    player1.updatePlayer1LedBuffer();
    player2.move(rightInput.x, speed);
    player2.updatePlayer2LedBuffer();
  }

  void Controller::incrementCurrentScore()
  {
    ++contextManager->stateManager.getDemoGameState().currentScore;
    contextManager->stateManager.displayShouldUpdate = true;
  }

  void Controller::incrementHighScore()
  {
    ++contextManager->stateManager.getDemoGameState().highScore;
    contextManager->stateManager.displayShouldUpdate = true;
  }
}