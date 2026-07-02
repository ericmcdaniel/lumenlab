#pragma once

#include "lights/color.h"
#include "lights/pixel.h"
#include <span.h>

namespace Lights
{
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

    CustomDataStructures::Span<const Pixel> getRendering() const { return CustomDataStructures::Span<const Pixel>(pixels.data(), N); }

    Pixel &operator[](uint16_t index) { return pixels[index]; }
    const Pixel &operator[](uint16_t index) const { return pixels[index]; }

    auto begin() { return pixels.begin(); }
    auto end() { return pixels.end(); }

    auto begin() const { return pixels.begin(); }
    auto end() const { return pixels.end(); }

    auto cbegin() const { return pixels.cbegin(); }
    auto cend() const { return pixels.cend(); }

  private:
    std::array<Pixel, N> pixels;
  };
}