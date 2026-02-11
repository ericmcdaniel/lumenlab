#include "games/phase-evasion/state.h"
#include "core/context-manager.h"
#include "logger.h"

namespace Games::PhaseEvasion
{
  void GameState::reset()
  {
    flaresEvaded = gemsCaptured = 0;
    highScore = contextManager->memory.getUInt(memoryKeyName);
  }

  uint16_t GameState::calculateTotalScore() const
  {
    return flaresEvaded + (2 * gemsCaptured);
  }

  void GameState::updateHighScore()
  {
    highScore = calculateTotalScore();
    contextManager->memory.putUInt(memoryKeyName, highScore);
    logf("High score updated: %u", highScore);
  }
}