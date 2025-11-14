#include "engine/timer.h"

namespace Engine
{
  void Timer::wait(uint32_t futureTime)
  {
    next = millis() + futureTime;
  }

  const bool Timer::isReady() const
  {
    return millis() >= next;
  }
}