#pragma once

#include "core/context-manager.h"
#include "games/phase-evasion/flare.h"

namespace Games::PhaseEvasion
{
  class FlareManager : public Engine::Timer
  {
  public:
    FlareManager(SystemCore::ContextManager *ctx) : contextManager{ctx} {}
    FlareManager(const FlareManager &) = delete;
    FlareManager &operator=(const FlareManager &) = delete;

    Flare &operator[](uint16_t index) { return flarePool[index]; }
    const Flare &operator[](uint16_t index) const { return flarePool[index]; }

    auto begin() { return flarePool.begin(); }
    auto end() { return flarePool.end(); }
    const auto begin() const { return flarePool.begin(); }
    const auto end() const { return flarePool.end(); }

    const size_t size() const;

    void updatePositions();
    void dispatch(float speed);
    void reset();

  private:
    SystemCore::ContextManager *contextManager;
    std::array<Flare, 10> flarePool;
  };
}