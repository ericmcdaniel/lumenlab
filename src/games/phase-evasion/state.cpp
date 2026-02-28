#include "games/phase-evasion/state.h"
#include "core/context-manager.h"
#include "logger.h"

namespace Games::PhaseEvasion
{
  void GameState::reset()
  {
    flaresEvaded = gemsCaptured = 0;
  }

  void GameState::loadHighScore()
  {
    highScore = contextManager->memory.getUInt(memoryKeyName, 0);
  }

  uint16_t GameState::calculateTotalScore() const
  {
    return flaresEvaded + (2 * gemsCaptured);
  }

  void GameState::checkHighScore()
  {
    const auto currentScore = calculateTotalScore();
    if (currentScore >= highScore)
    {
      updateHighScore(currentScore);
      highScore = currentScore;
      contextManager->stateManager.displayShouldUpdate = true;
    }
  }

  void GameState::updateHighScore(uint16_t newHighScore)
  {
    contextManager->memory.putUInt(memoryKeyName, newHighScore);
    logf("High score updated: %u", newHighScore);
  }
}