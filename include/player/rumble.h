#pragma once

#include <cstddef>

#include "common.h"

namespace Player
{
  enum class RumbleOptions
  {
    SingleQuickPulse,
    DoubleQuickPulse,
    DeathPulse
  };

  struct RumbleStep
  {
    int intensity;
    int duration;
  };

  class RumblePattern
  {
  public:
    template <uint16_t N>
    RumblePattern(const RumbleStep (&steps)[N]) : steps(steps), count(N) {}

    const RumbleStep *getSteps() const { return steps; }
    size_t getCount() const { return count; }

  private:
    const RumbleStep *steps;
    size_t count;
  };

  static const RumbleStep singleQuickSteps[] = {
      {200, 100}};
  static const RumbleStep doubleQuickSteps[] = {
      {200, 100},
      {0, 100},
      {200, 100}};
  static const RumbleStep deathSteps[] = {
      {255, 100},
      {0, 100},
      {255, 400},
      {0, 100},
      {255, 100},
      {0, 100},
      {255, 400}};
  static const RumblePattern singleQuickRumbleSeq{singleQuickSteps};
  static const RumblePattern doubleQuickRumbleSeq{doubleQuickSteps};
  static const RumblePattern deathRumbleSeq{deathSteps};

}