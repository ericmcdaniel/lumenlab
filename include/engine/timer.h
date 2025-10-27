#pragma once

#include <Arduino.h>

namespace Engine
{
  class Timer
  {
  public:
    Timer() = default;
    virtual ~Timer() = default;

    void wait(unsigned long futureTime);
    void waitFromNow(unsigned long futureTime);
    const bool isReady();
    unsigned long nextOccurrence() { return next; }

  private:
    unsigned long next{millis()};
  };
}