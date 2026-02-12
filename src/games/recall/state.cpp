#include "games/phase-evasion/state.h"
#include "core/context-manager.h"
#include "logger.h"

namespace Games::Recall
{

  GameState::GameState(SystemCore::ContextManager *ctx) : contextManager{ctx}
  {
    reset();
  }

  void GameState::reset()
  {
    round = 0;
    highScore = contextManager->memory.getUInt(memoryKeyName);
    contextManager->stateManager.displayShouldUpdate = true;
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