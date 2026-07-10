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
    Player(SystemCore::ContextManager *ctx, const uint16_t width, ColorPalette profile) : ::Player::BasePlayer{ctx, width}
    {
      setColorPalette(profile);
    };
    void setColorPalette(ColorPalette profile)
    {
      if (profile == ColorPalette::Red)
      {
        pixels = {
            {0xff0000, 0x40},
            {0xff0000, 0x80},
            {0xff0000, 0xa0},
            {0xff0000, 0xc0},
            {0xff8888, 0xe8},
            {0xfff0f0, 0xff},
            {0xff8888, 0xe8},
            {0xff0000, 0xc0},
            {0xff0000, 0xa0},
            {0xff0000, 0x80},
            {0xff0000, 0x40}};
        layer = Engine::Layer::GameLayer_2;
        positionPrecise = 50.0f;
      }
      else
      {
        pixels = {
            {0x0000ff, 0x40},
            {0x0000ff, 0x80},
            {0x0000ff, 0xa0},
            {0x0000ff, 0xc0},
            {0x8888ff, 0xe8},
            {0xf0f0ff, 0xff},
            {0x8888ff, 0xe8},
            {0x0000ff, 0xc0},
            {0x0000ff, 0xa0},
            {0x0000ff, 0x80},
            {0x0000ff, 0x40}};
        layer = Engine::Layer::GameLayer_1;
      }
    }
    void updatePlayer1LedBuffer();
    void updatePlayer2LedBuffer();

    Engine::Layer layer;

    CustomDataStructures::Span<const Lights::Pixel> getRendering() const override { return pixels.getRendering(); }
    float getPositionPrecise() const override { return ::Player::BasePlayer::positionPrecise; }
    Engine::Layer getLayer() const override { return layer; }

  private:
    Lights::Pixels<11> pixels;
  };
}