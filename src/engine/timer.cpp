#include "engine/timer.h"

namespace Engine
{
  void Timer::wait(unsigned long futureTime)
  {
    // if (futureTime <= 0)
    // {
    // }
    next = next + futureTime;
  }

  const bool Timer::isReady()
  {
    return millis() >= next;
  }
}