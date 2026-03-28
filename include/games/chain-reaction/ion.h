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
    static constexpr uint8_t width = 5;

    uint16_t getPosition() const { return static_cast<uint16_t>(positionFloat); }
    void updatePosition();
    void assignColors();
    const bool isActive() const { return active; }

    std::vector<Lights::Color> elements;

  private:
    float positionFloat;
    float speed;
    uint8_t capacity;
    bool active = true;
  };
}