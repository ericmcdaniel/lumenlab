#include "engine/timer.h"

namespace Engine
{
  void Timer::wait(unsigned long futureTime)
  {
    next = next + futureTime;
  }

  void Timer::resettedWait(unsigned long futureTime)
  {
    next = millis() + futureTime;
  }

  const bool Timer::isReady()
  {
    return millis() >= next;
  }
}