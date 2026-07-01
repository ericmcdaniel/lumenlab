#pragma once

#include "lights/color.h"
#include "engine/layer.h"

namespace Engine
{
  struct Pixel
  {
    Lights::Color color;
    uint8_t alpha;
    Layer layer = Engine::Layer::Background;
  };

  template <uint16_t N>
  class Pixels
  {
  public:
    std::array<Pixel, N> pixels;

    Pixels() = default;
    Pixels(std::initializer_list<Pixel> list)
    {
      uint16_t index = 0;
      for (const auto &pixel : list)
      {
        if (index >= N)
          break;
        pixels[index++] = pixel;
      }
    }

    Pixel &operator[](uint16_t index) { return pixels[index]; }
    const Pixel &operator[](uint16_t index) const { return pixels[index]; }

    auto begin() { return pixels.begin(); }
    auto end() { return pixels.end(); }

    auto begin() const { return pixels.begin(); }
    auto end() const { return pixels.end(); }

    auto cbegin() const { return pixels.cbegin(); }
    auto cend() const { return pixels.cend(); }
  };
}