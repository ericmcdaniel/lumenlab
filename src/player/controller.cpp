#include "player/controller.h"
#include "common.h"

namespace Player
{
  int Controller::filterDeadZone(int8_t value, int deadZone)
  {
    if (std::abs(value) <= deadZone)
      return 0;

    constexpr float responseExponent = 1.5f;
    const int8_t maxRaw = 127;

    float sign = (value > 0) ? 1.0f : -1.0f;
    float magnitude = static_cast<float>(std::abs(value) - deadZone);
    float normalizedAnalogValue = magnitude / static_cast<float>(maxRaw - deadZone);
    normalizedAnalogValue = std::clamp(normalizedAnalogValue, 0.0f, 1.0f);

    float scaled = std::pow(normalizedAnalogValue, responseExponent);
    int output = static_cast<int>(std::round(scaled * static_cast<float>(maxRaw)));
    return static_cast<int>(sign * output);
  }

  void Controller::reset()
  {
    for (uint32_t i = 0; i < arraySize(buttonPressedEvent); ++i)
    {
      buttonPressedEvent[i] = false;
      buttonReleasedEvent[i] = false;
      buttonLastState[i] = rawButtonState(static_cast<ControllerButton>(i));
      buttonDebouceEvent[i] = 0;
    }
  }
}