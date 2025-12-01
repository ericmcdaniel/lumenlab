#pragma once

#include "lights/color-code.h"

namespace Games
{
  class PhaseEvasionFlare
  {
  public:
    PhaseEvasionFlare()
    {
      color = Lights::ColorCode::MenuLightBlue;
    };

  private:
    Lights::ColorCode color;
  };
}