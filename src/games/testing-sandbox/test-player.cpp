#include <stdlib.h>

#include "games/testing-sandbox/test-player.h"

namespace Games
{

  void TestPlayer::move(const int distance)
  {
    int delta = distance / 20;

    position = (position + delta) % static_cast<int>(contextManager->leds.size());
    if (position < 0)
      position += static_cast<int>(contextManager->leds.size()) - abs(delta);
  }

  void TestPlayer::updatePlayer1LedBuffer()
  {
    for (int i = 0; i <= width; ++i)
    {
      size_t index = (position + i) % contextManager->leds.size();
      contextManager->leds.buffer[index].r() = static_cast<int>(245.0 * (1.0 - abs(i - 4) / 4.0));
      contextManager->leds.buffer[index].g() = static_cast<int>(215.0 * (1.0 - abs(i - 4) / 4.0));
      contextManager->leds.buffer[index].b() = static_cast<int>(128.0 * (1.0 - abs(i - 4) / 4.0));
    }
  }

  void TestPlayer::updatePlayer2LedBuffer()
  {
    for (int i = 0; i <= width; ++i)
    {
      size_t index = (position + i) % contextManager->leds.size();
      contextManager->leds.buffer[index].r() = static_cast<int>(103.0 * (1.0 - abs(i - 4) / 4.0));
      contextManager->leds.buffer[index].g() = static_cast<int>(162.0 * (1.0 - abs(i - 4) / 4.0));
      contextManager->leds.buffer[index].b() = static_cast<int>(235.0 * (1.0 - abs(i - 4) / 4.0));
    }
  }
}