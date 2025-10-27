#pragma once

namespace Engine
{
  class Layer
  {
  public:
    Layer() {};
    virtual void nextEvent() = 0;
  };
}