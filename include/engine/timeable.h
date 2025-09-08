#pragma once

#include <Arduino.h>
#include "engine/run-state.h"

namespace Time
{

  class Timeable
  {
  private:
    Engine::RunState &currentState;
    unsigned long next{micros()};

  public:
    Timeable(Engine::RunState &state) : currentState(state) {};
    virtual ~Timeable() = default;

    void setTime(unsigned long futureTime);
    const bool isReady() const;
  };
}