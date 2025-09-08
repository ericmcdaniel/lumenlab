#include "engine/engine.h"

namespace Engine
{
  void GameEngine::runApplication()
  {
    while (this->currentAction != RunState::ERROR)
    {
      switch (this->currentAction)
      {
      case RunState::INITIALIZE:
        GameEngine::handleStartup();
        break;

      default:
        break;
      }
    }
  }

  void GameEngine::handleStartup()
  {
  }
}