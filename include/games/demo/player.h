#pragma once

#include "platform/context-manager.h"
#include "engine/render-model.h"
#include "player/player.h"
#include "lights/pixels.h"
#include <span.h>

namespace Games::Demo
{
  class Player : public ::Player::BasePlayer, public Engine::RenderModel
  {
  public:
    Player(SystemCore::ContextManager *ctx, const uint16_t width) : ::Player::BasePlayer{ctx, width}
    {
      pixels = {
          {0xff0000, 0x40},
          {0xed1c24, 0xa0},
          {0xff8888, 0xe0},
          {0xffffff, 0xff},
          {0xff8888, 0xe0},
          {0xed1c24, 0xa0},
          {0xff0000, 0x40}};
    };
    Engine::Layer layer = Engine::Layer::GameLayer_1;
    void updatePlayer1LedBuffer();
    void updatePlayer2LedBuffer();

    CustomDataStructures::Span<const Lights::Pixel> getRendering() const override { return pixels.getRendering(); }
    float getPositionPrecise() const override { return ::Player::BasePlayer::positionPrecise; }
    Engine::Layer getLayer() const override { return layer; }

  private:
    Lights::Pixels<7> pixels;
  };
}