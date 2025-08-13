#include "Arduino.h"

#include "Timeable.h"

namespace Time
{
  inline const bool Timeable::isReady() const
  {
    return millis() <= this->next;
  }
}