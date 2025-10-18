#pragma once

#include <stdint.h>

// Minimal standalone CRGB equivalent
struct CRGB
{
  union
  {
    struct
    {
      uint8_t r, g, b;
    };
    uint8_t raw[3];
  };

  constexpr CRGB() : r(0), g(0), b(0) {}
  constexpr CRGB(uint8_t red, uint8_t green, uint8_t blue)
      : r(red), g(green), b(blue) {}

  // Optional helpers
  inline void setRGB(uint8_t red, uint8_t green, uint8_t blue)
  {
    r = red;
    g = green;
    b = blue;
  }
  inline void clear() { r = g = b = 0; }
};

namespace fl
{
  // 8-bit types - char is reliably 8 bits on all supported platforms
  // These must be defined BEFORE platform includes so fractional types can use them
  typedef signed char i8;
  typedef unsigned char u8;
  typedef unsigned int uint;

  // Pointer and size types are defined per-platform in platforms/int.h
  // uptr (pointer type) and size (size type) are defined per-platform

}
