#include "Arduino.h"

#include "engine/timeable.h"

namespace Time
{
  void Timeable::setTime(unsigned long futureTime)
  {
    if (futureTime <= 0)
    {
    }
  }

  const bool Timeable::isReady() const
  {
    return micros() <= this->next;
  }
}