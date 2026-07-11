#pragma once

#include "platform/context-manager.h"
#include "engine/render-model.h"
#include "player/player.h"
#include "lights/pixels.h"
#include <span.h>

namespace Games::Demo
{

  enum class ColorPalette
  {
    Red,
    Blue
  };

  class Player : public ::Player::BasePlayer, public Engine::RenderModel
  {
  public:
    Player(SystemCore::ContextManager *ctx, ColorPalette profile) : ::Player::BasePlayer{ctx, width}
    {
      setColorPalette(profile);
    };
    void setColorPalette(ColorPalette profile)
    {
      if (profile == ColorPalette::Red)
      {
        pixels = {
            {0xff4d4d, 0x40},
            {0xff4d4d, 0x80},
            {0xff4d4d, 0xa0},
            {0xff4d4d, 0xe8},
            {0xff8888, 0xe8},
            {0xfff0f0, 0xff},
            {0xff8888, 0xe8},
            {0xff4d4d, 0xe8},
            {0xff4d4d, 0xa0},
            {0xff4d4d, 0x80},
            {0xff4d4d, 0x40}};
        layer = Engine::Layer::GameLayer_2;
        positionPrecise = 50.0f;
      }
      else
      {
        pixels = {
            {0x4da6ff, 0x40},
            {0x4da6ff, 0x80},
            {0x4da6ff, 0xa0},
            {0x4da6ff, 0xe8},
            {0x8ec8ff, 0xe8},
            {0xf0f0ff, 0xff},
            {0x8ec8ff, 0xe8},
            {0x4da6ff, 0xe8},
            {0x4da6ff, 0xa0},
            {0x4da6ff, 0x80},
            {0x4da6ff, 0x40}};
        layer = Engine::Layer::GameLayer_1;
      }
    }

    Engine::Layer layer;

    CustomDataStructures::Span<const Lights::Pixel> getRendering() const override { return pixels.getRendering(); }
    float getPositionPrecise() const override { return ::Player::BasePlayer::positionPrecise; }
    Engine::Layer getLayer() const override { return layer; }

  private:
    static constexpr uint16_t width = 11;
    Lights::Pixels<width> pixels;
  };
}