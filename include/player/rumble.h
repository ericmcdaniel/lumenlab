#pragma once

namespace Player
{
  enum class RumbleOptions
  {
    DoublePulse
  };

  struct RumbleStep
  {
    int intensity;
    int duration;
  };
}