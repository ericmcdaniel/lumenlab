#include "games/demo/game-main.h"
#include "player/controller.h"
#include "logger.h"

namespace Games::Demo
{
  void GameMain::nextEvent()
  {
    if (contextManager->controller.wasPressed(::Player::ControllerButton::Cross))
    {
      incrementCurrentScore();
      contextManager->stateManager.displayShouldUpdate = true;
      contextManager->controller.rumble(::Player::RumbleOptions::SingleQuickPulse);
      logf("Current score: %d", getCurrentScore());
    }
    auto leftInput = contextManager->controller.leftAnalog();
    auto rightInput = contextManager->controller.rightAnalog();
    player1.move(leftInput.x, speed);
    player2.move(rightInput.x, speed);

    // player1.updatePlayer1LedBuffer();
    // player2.updatePlayer2LedBuffer();
    render();
  }

  void GameMain::render()
  {
    auto &renderer = contextManager->renderer;
    renderer.renderEntity(player1);
    renderer.renderEntity(player2);
  }

  void GameMain::incrementCurrentScore()
  {
    ++contextManager->stateManager.getDemoGameState().currentScore;
    contextManager->stateManager.displayShouldUpdate = true;
  }

  void GameMain::incrementHighScore()
  {
    ++contextManager->stateManager.getDemoGameState().highScore;
    contextManager->stateManager.displayShouldUpdate = true;
  }
}