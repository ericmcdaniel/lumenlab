#pragma once

#include "games/chain-reaction/ion.h"
#include "core/context-manager.h"

namespace Games::ChainReaction
{
  class IonCannon
  {
  public:
    IonCannon(SystemCore::ContextManager *ctx) : contextManager{ctx} {}
    IonCannon(const IonCannon &) = delete;

    static constexpr uint8_t ionWidth = 6;

    IonCannon &operator=(const IonCannon &) = delete;

    Ion &operator[](uint16_t index) { return ionPool[index]; }
    const Ion &operator[](uint16_t index) const { return ionPool[index]; }

    auto begin() { return ionPool.begin(); }
    auto end() { return ionPool.end(); }
    const auto begin() const { return ionPool.begin(); }
    const auto end() const { return ionPool.end(); }

    const size_t size() const { return ionPool.size(); }

    const size_t shouldDispatch() const;
    void dispatch();
    void reset();

  private:
    SystemCore::ContextManager *contextManager;
    std::vector<Ion> ionPool;
  };
}