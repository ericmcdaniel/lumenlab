#include "games/reflex/signal.h"

namespace Games::Reflex
{
  Signal::Signal(SystemCore::ContextManager *ctx, uint16_t width, float _speed) : ::Player::BasePlayer{ctx, width},
                                                                                  speed{_speed} {}
}