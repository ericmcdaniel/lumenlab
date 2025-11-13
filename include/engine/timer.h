#pragma once

#include <Arduino.h>

namespace Engine
{
  class Timer
  {
  public:
    Timer() = default;
    virtual ~Timer() = default;

    void wait(uint32_t futureTime);
    const bool isReady() const;
    uint32_t nextOccurrence() { return next; }

  private:
    uint32_t next{millis()};
  };
}