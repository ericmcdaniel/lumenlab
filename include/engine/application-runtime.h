#pragma once

namespace Engine
{
  class ApplicationRuntime
  {
  public:
    virtual void nextEvent() = 0;
  };
}