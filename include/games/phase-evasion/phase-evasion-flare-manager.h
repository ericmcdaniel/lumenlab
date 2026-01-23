#pragma once

#include "games/phase-evasion/phase-evasion-flare.h"

namespace Games::PhaseEvasion
{
  class FlareManager : public Engine::Timer
  {
  public:
    FlareManager();

    Flare &operator[](uint16_t index) { return flares[index]; }
    const Flare &operator[](uint16_t index) const { return flares[index]; }

    fl::vector<Flare>::iterator begin() { return flares.begin(); }
    fl::vector<Flare>::iterator end() { return flares.end(); }
    fl::vector<Flare>::const_iterator begin() const { return flares.begin(); }
    fl::vector<Flare>::const_iterator end() const { return flares.end(); }

    fl::size size() { return flares.size(); }

    void updatePositions();
    void dispatch();

  private:
    fl::vector<Flare> flares;
  };
}