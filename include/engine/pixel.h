#pragma once

// #include <cstdint>
#include "lights/color.h"

namespace Engine
{
  struct Pixel
  {
    Lights::Color color;
    uint8_t alpha;
    // Layer layer;
  };

  template <uint16_t N>
  class Pixels
  {
  public:
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
    std::array<Pixel, N> pixels;

    Pixel &operator[](uint16_t index) { return pixels[index]; }
    const Pixel &operator[](uint16_t index) const { return pixels[index]; }
  };
}