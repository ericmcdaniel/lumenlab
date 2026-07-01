#pragma once

#include "platform/context-manager.h"
#include "player/player.h"
#include "engine/renderable.h"

namespace Games::Demo
{
  class Player : public ::Player::BasePlayer //, public Engine::Renderable<5>
  {
  public:
    Player(SystemCore::ContextManager *ctx, const uint16_t width) : ::Player::BasePlayer{ctx, width}
    {
      pixels = {
          Engine::Pixel{Lights::Color{0xffffff}, 0x44},
          Engine::Pixel{Lights::Color{0xffffff}, 0x88},
          Engine::Pixel{Lights::Color{0xffffff}, 0xff},
          Engine::Pixel{Lights::Color{0xffffff}, 0x80},
          Engine::Pixel{Lights::Color{0xffffff}, 0x40}};
    };
    void updatePlayer1LedBuffer();
    void updatePlayer2LedBuffer();

    const Engine::Pixels<5> &getRendering() const;

  private:
    Engine::Pixels<5> pixels;
  };
}