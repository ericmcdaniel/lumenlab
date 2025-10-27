#pragma once

#include <Ps3Controller.h> // Needed only for the uint16_t definition

namespace Games
{
  enum class ActivePlayer
  {
    Computer,
    Player
  };

  class RecallGameState
  {
  public:
    RecallGameState() : highScore{0}, round{0} {}
    void reset() { highScore = round = 0; }
    uint16_t highScore;
    uint16_t round;
  };
}