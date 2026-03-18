#pragma once

#include "engine/timer.h"
#include "lights/color.h"

namespace Games::ChainReaction
{
  class Ion : public Engine::Timer
  {
  public:
    Ion() { Ion(maxIonElements); }
    Ion(uint8_t cap);
    ~Ion() = default;

    uint16_t getPosition() const { return position; }
    void assignColors();

    static constexpr uint8_t maxIonElements = 3;
    static constexpr uint8_t elementWidth = 3;

  private:
    uint16_t position;
    uint8_t capacity;
    std::vector<Lights::Color> elements;
  };
}