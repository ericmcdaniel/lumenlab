#include "games/phase-evasion/state.h"
#include "core/context-manager.h"
#include "logger.h"

namespace Games::Recall
{

  void GameState::reset()
  {
    round = 0;
    highScore = contextManager->memory.getUInt(memoryKeyName);
  }

  void GameState::updateHighScore()
  {
    highScore = round;
    contextManager->memory.putUInt(memoryKeyName, highScore);
    logf("High score updated: %u", highScore);
  }
}