#include "games/testing-sandbox/test-core.h"
#include "player/controller.h"
#include "logger.h"

namespace Games
{
  void TestCore::nextEvent()
  {
    auto input = controller.leftAnalog();
    auto input2 = controller.rightAnalog();
    player->move(input.x);
    player->updateLedBuffer();
    player2->move(input2.x);
    player2->updateLedBuffer2();
  }
}