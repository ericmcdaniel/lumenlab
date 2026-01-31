#include "games/phase-evasion/flare.h"

namespace Games::PhaseEvasion
{
  void Flare::updatePosition()
  {
    positionFloat -= speed;
    if (positionFloat <= 0.0f)
    {
      active = false;
      color = Lights::Color::WhiteSmoke;
      completedCycle = true;
    }
  }

  void Flare::activate(Lights::Color _color, float _speed)
  {
    active = true;
    completedCycle = false;
    color = _color;
    speed = _speed;
    positionFloat = static_cast<float>(SystemCore::Configuration::numLeds + width);
  }

  void Flare::deactivate()
  {
    active = false;
  }
}