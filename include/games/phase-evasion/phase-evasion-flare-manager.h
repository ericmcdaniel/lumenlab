#pragma once

#include "engine/timer.h"
#include "games/phase-evasion/phase-evasion-flare.h"

namespace Games
{
  class PhaseEvasionFlareManager : public Engine::Timer
  {
  public:
    PhaseEvasionFlareManager(Core::ContextManager *ctx);

    PhaseEvasionFlare &operator[](uint16_t index) { return flares[index]; }
    const PhaseEvasionFlare &operator[](uint16_t index) const { return flares[index]; }
    fl::vector<PhaseEvasionFlare>::iterator begin() { return flares.begin(); }
    fl::vector<PhaseEvasionFlare>::iterator end() { return flares.end(); }
    fl::vector<PhaseEvasionFlare>::const_iterator begin() const { return flares.begin(); }
    fl::vector<PhaseEvasionFlare>::const_iterator end() const { return flares.end(); }

  private:
    Core::ContextManager *contextManager;
    fl::vector<PhaseEvasionFlare> flares;
  };
}