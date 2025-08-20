#include "Arduino.h"

#include "Timeable.h"

namespace Time
{
  const bool Timeable::isReady() const
  {
    return micros() <= this->next;
  }
}