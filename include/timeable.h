#pragma once

#include <Arduino.h>

namespace Time
{

  class Timeable
  {
  protected:
    unsigned long next{micros()};

  public:
    Timeable() = default;
    virtual ~Timeable() = default;

    const bool isReady() const;
  };
}