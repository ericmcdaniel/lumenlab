#include "games/demo/game-main.h"
#include "player/controller.h"
#include "logger.h"

namespace Games::Demo
{
  void GameMain::nextEvent()
  {
    switch (state.current)
    {
    case Actions::Active:
      readInput();
      updatePosition();
      render();
      break;
    }
  }

  void GameMain::readInput()
  {
    if (contextManager->controller.wasPressed(::Player::ControllerButton::Cross))
    {
      incrementCurrentScore();
      contextManager->controller.rumble(::Player::RumbleOptions::SingleQuickPulse);
      logf("Current score: %d", state.currentScore);
    }
  }

  void GameMain::updatePosition()
  {
    auto leftInput = contextManager->controller.leftAnalog();
    auto rightInput = contextManager->controller.rightAnalog();
    player1.move(leftInput.x, speed);
    player2.move(rightInput.x, speed);
  }

  void GameMain::render()
  {
    // player1.updatePlayer1LedBuffer();
    // player2.updatePlayer2LedBuffer();
    Engine::Renderer &renderer = contextManager->renderer;
    renderer.renderEntity(player1);
    renderer.renderEntity(player2);
  }

  void GameMain::incrementCurrentScore()
  {
    ++state.currentScore;
    contextManager->stateManager.displayShouldUpdate = true;
  }

  void GameMain::incrementHighScore()
  {
    ++state.highScore;
    contextManager->stateManager.displayShouldUpdate = true;
  }
}