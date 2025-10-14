#pragma once

#include <Arduino.h>
#include "engine/run-state.h"

namespace Engine
{
  class Timer
  {
  private:
    unsigned long next{millis()};

  public:
    Timer() = default;
    virtual ~Timer() = default;

    void wait(unsigned long futureTime);
    const bool isReady();
    unsigned long nextOccurrence() { return next; }
  };
}