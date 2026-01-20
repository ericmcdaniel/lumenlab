#pragma once

#include "engine/timer.h"
#include "games/phase-evasion/phase-evasion-flare.h"

namespace Games
{
  class PhaseEvasionFlareManager : public Engine::Timer
  {
  public:
    PhaseEvasionFlare &operator[](uint16_t index) { return flares[index]; }
    const PhaseEvasionFlare &operator[](uint16_t index) const { return flares[index]; }
    fl::vector<PhaseEvasionFlare> flares;

  private:
  };
}