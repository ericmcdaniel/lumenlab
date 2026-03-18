#pragma once

#include "games/chain-reaction/ion.h"

namespace Games::ChainReaction
{
  class IonCannon
  {
  public:
    IonCannon() {}
    IonCannon(const IonCannon &) = delete;
    IonCannon &operator=(const IonCannon &) = delete;

    Ion &operator[](uint16_t index) { return ions[index]; }
    const Ion &operator[](uint16_t index) const { return ions[index]; }

    auto begin() { return ions.begin(); }
    auto end() { return ions.end(); }
    const auto begin() const { return ions.begin(); }
    const auto end() const { return ions.end(); }

    const size_t size() const { return ions.size(); }

    void updatePositions();
    void dispatch(float speed);
    void reset();

  private:
    // SystemCore::ContextManager *contextManager;
    std::vector<Ion> ions;
  };
}