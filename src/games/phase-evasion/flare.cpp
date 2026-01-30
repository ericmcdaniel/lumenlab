#include "games/phase-evasion/flare.h"

namespace Games::PhaseEvasion
{
  void Flare::updatePosition()
  {
    if (positionFloat <= 0.0f)
    {
      active = false;
      color = Lights::Color::WhiteSmoke;
    }
    else
    {
      positionFloat -= speed;
    }
  }

  void Flare::activate(Lights::Color _color, float _speed)
  {
    active = true;
    color = _color;
    speed = _speed;
    positionFloat = static_cast<float>(SystemCore::Configuration::numLeds + width);
  }

  void Flare::deactivate()
  {
    active = false;
  }
}