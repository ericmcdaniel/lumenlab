#include "engine/timeable.h"

namespace Time
{
  void Timeable::wait(unsigned long futureTime)
  {
    // if (futureTime <= 0)
    // {
    // }
    next = next + futureTime;
  }

  const bool Timeable::isReady()
  {
    return millis() >= next;
  }
}