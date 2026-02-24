#include "games/recall/state.h"
#include "core/context-manager.h"
#include "logger.h"

namespace Games::Recall
{

  void GameState::reset()
  {
    round = 0;
    contextManager->stateManager.displayShouldUpdate = true;
  }

  void GameState::loadHighScore()
  {
    highScore = contextManager->memory.getUInt(memoryKeyName, 0);
  }

  void GameState::updateHighScore()
  {
    highScore = round;
    contextManager->memory.putUInt(memoryKeyName, highScore);
    logf("High score updated: %u", highScore);
  }

  void GameState::incrementScore()
  {
    ++round;
    if (round > highScore)
    {
      updateHighScore();
    }
    contextManager->stateManager.displayShouldUpdate = true;
  }
}