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

    static constexpr uint8_t maxIonElements = 3;

    uint16_t getPosition() const { return position; }
    void assignColors();
    const bool isActive() const { return active; }

    std::vector<Lights::Color> elements;

  private:
    uint16_t position;
    uint8_t capacity;
    bool active = true;
  };
}