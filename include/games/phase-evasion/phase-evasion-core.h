#pragma once

#include "engine/layer.h"

namespace Game
{
  class PhaseEvasion : Engine::Layer
  {
    PhaseEvasion() {}
    void nextEvent() override;
  };
}