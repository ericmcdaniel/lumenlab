#include "Arduino.h"

#include "timeable.h"

namespace Time
{
  const bool Timeable::isReady() const
  {
    return micros() <= this->next;
  }
}