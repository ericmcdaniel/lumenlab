#include "engine/timer.h"

namespace Engine
{
  void Timer::wait(unsigned long futureTime)
  {
    next = millis() + futureTime;
  }

  const bool Timer::isReady() const
  {
    return millis() >= next;
  }
}