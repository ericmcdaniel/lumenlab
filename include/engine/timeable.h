#pragma once

#include <Arduino.h>
#include "engine/run-state.h"

namespace Time
{
  class Timeable
  {
  private:
    unsigned long next{millis()};

  public:
    Timeable() = default;
    virtual ~Timeable() = default;

    void wait(unsigned long futureTime);
    const bool isReady();
    unsigned long nextOccurrence() { return next; }
  };
}