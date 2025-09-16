#include "Arduino.h"

#include "engine/timeable.h"

namespace Time
{
  void Timeable::setTime(unsigned long futureTime)
  {
    // if (futureTime <= 0)
    // {
    // }
    next = futureTime;
  }

  const bool Timeable::isReady()
  {
    return millis() >= this->next;
    // next = millis() + 10000000;
  }
}