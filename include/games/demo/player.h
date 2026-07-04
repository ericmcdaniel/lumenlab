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
          {Lights::ColorCode::ThemeRed, 0x44},
          {Lights::ColorCode::ThemeRed, 0x88},
          {Lights::ColorCode::ThemeRed, 0xff},
          {Lights::ColorCode::MenuUnselected, 0xff},
          {Lights::ColorCode::ThemeRed, 0xff},
          {Lights::ColorCode::ThemeRed, 0x80},
          {Lights::ColorCode::ThemeRed, 0x40}};
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