#pragma once

#include "Timeable.h"

namespace Lights
{

  class LedStrip : protected Time::Timeable
  {
  public:
    LedStrip();
    void getColors();
  };
}