#pragma once

#include "engine/timer.h"
#include "lights/color.h"

namespace Games::ChainReaction
{
  class Ion : public Engine::Timer
  {
  public:
    Ion() { Ion(maxIonColors); }
    Ion(uint8_t size);
    ~Ion() = default;

    static constexpr uint8_t maxIonColors = 3;

    const uint8_t getSize() const { return colors.size(); }

    uint16_t getPosition() const { return static_cast<uint16_t>(positionFloat); }
    void updatePosition();

    const std::vector<Lights::Color> &getColors() const { return colors; };
    void assignColors(uint8_t s);

    const bool isActive() const { return active; }

    std::vector<Lights::Color> colors;

  private:
    float positionFloat;
    float speed;
    bool active = true;
  };
}