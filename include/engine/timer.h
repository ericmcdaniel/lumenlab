#pragma once

#include <Arduino.h>
#include "engine/state-manager.h"

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
    void resettedWait(unsigned long futureTime);
    const bool isReady();
    unsigned long nextOccurrence() { return next; }
  };
}