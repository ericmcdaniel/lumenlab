#pragma once

#include "lights/pixel.h"
#include "engine/layer.h"

#include <span.h>

namespace Engine
{
  class RenderModel
  {
  public:
    virtual CustomDataStructures::Span<const Lights::Pixel> getRendering() const = 0;
    virtual float getPositionPrecise() const = 0;
    virtual Layer getLayer() const = 0;
  };
}