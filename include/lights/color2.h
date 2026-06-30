#pragma once

#include <algorithm>
#include <FastLED.h>
#include "lights/color-code.h"
#include "engine/layer.h"
#include <cstdint>

namespace Lights
{
  class Color2 : public CRGB
  {
  public:
    using CRGB::CRGB;
    Color2() : CRGB(), layer{Engine::Layer::Background} {}
    Color2(uint8_t r, uint8_t g, uint8_t b, Engine::Layer l) : CRGB(r, g, b), layer{l} {}
    Color2(uint8_t r, uint8_t g, uint8_t b) : CRGB(r, g, b), layer{Engine::Layer::Background} {}
    Color2(ColorCode color, Engine::Layer l) : CRGB{static_cast<uint32_t>(color)}, layer{l} {}
    Color2(ColorCode color) : CRGB{static_cast<uint32_t>(color)}, layer{Engine::Layer::Background} {}

    Engine::Layer layer;

    Color2 operator*(double scale) const;
    Color2 operator*(uint8_t scale) const;
    Color2 operator/(double scale) const;
    Color2 operator/(uint8_t scale) const;
    Color2 &operator*=(double scale);
  };

  inline const Color2 colorPalette2[4] = {
      Color2{ColorCode::ThemeBlue},
      Color2{ColorCode::ThemeRed},
      Color2{ColorCode::ThemeGreen},
      Color2{ColorCode::ThemeYellow}};
}