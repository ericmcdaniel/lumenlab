#pragma once

#include "platform/context-manager.h"
#include "player/player.h"
#include "lights/pixels.h"
#include <span.h>

namespace Games::Demo
{
  class Player : public ::Player::BasePlayer
  {
  public:
    Player(SystemCore::ContextManager *ctx, const uint16_t width) : ::Player::BasePlayer{ctx, width}
    {
      pixels = {
          Lights::Pixel{Lights::ColorCode::ThemeRed, 0x44},
          Lights::Pixel{Lights::ColorCode::ThemeRed, 0x88},
          Lights::Pixel{Lights::ColorCode::ThemeRed, 0xff},
          Lights::Pixel{Lights::ColorCode::ThemeRed, 0x80},
          Lights::Pixel{Lights::ColorCode::ThemeRed, 0x40}};
    };
    void updatePlayer1LedBuffer();
    void updatePlayer2LedBuffer();

    CustomDataStructures::Span<const Lights::Pixel> getRendering() const { return pixels.getRendering(); }

  private:
    Lights::Pixels<5> pixels;
  };
}