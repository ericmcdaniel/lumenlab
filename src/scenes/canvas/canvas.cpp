#include "scenes/canvas/canvas.h"
#include "esp_system.h"
#include "logger.h"
#include <limits>

namespace Scenes
{

  Canvas::Canvas(Core::ContextManager *ctx) : contextManager{ctx}
  {
    reset();
  }

  void Canvas::nextEvent()
  {
    checkColorChange();
    checkNewColorRequest();

    for (uint16_t i; i < contextManager->leds.size(); ++i)
    {
      contextManager->leds.buffer[i] = currentColor;
    }
  }

  void Canvas::checkColorChange()
  {
    bool hasChange = false;

    if (contextManager->controller.leftAnalog().x > 64)
    {
      colorHsl.hue = (colorHsl.hue - 1) % 255;
      hasChange = true;
    }
    if (contextManager->controller.leftAnalog().x < -64)
    {
      colorHsl.hue = (colorHsl.hue + 1) % 255;
      hasChange = true;
    }
    if (contextManager->controller.leftAnalog().y > 64)
    {
      colorHsl.saturation = std::clamp(colorHsl.saturation - 1, 0, 255);
      hasChange = true;
    }
    if (contextManager->controller.leftAnalog().y < -64)
    {
      colorHsl.saturation = std::clamp(colorHsl.saturation + 1, 0, 255);
      hasChange = true;
    }
    if (contextManager->controller.rightAnalog().y > 64)
    {
      colorHsl.value = std::clamp(colorHsl.value - 1, 0, 255);
      hasChange = true;
    }
    if (contextManager->controller.rightAnalog().y < -64)
    {
      colorHsl.value = std::clamp(colorHsl.value + 1, 0, 255);
      hasChange = true;
    }

    if (hasChange)
    {
      currentColor = colorHsl.toColor();
      logf("Color changed to Color(r=%u, g=%u, b=%u)", currentColor.r, currentColor.g, currentColor.b);
    }
  }

  void Canvas::checkNewColorRequest()
  {
    if (contextManager->controller.wasPressed(Player::ControllerButton::Triangle))
    {
      reset();
    }
  }

  void Canvas::reset()
  {
    colorHsl.hue = static_cast<uint8_t>(esp_random() % std::numeric_limits<uint8_t>::max());
    colorHsl.saturation = static_cast<uint8_t>((esp_random() % 64u) + 191u);
    colorHsl.value = static_cast<uint8_t>((esp_random() % 64u) + 96u);
    currentColor = colorHsl.toColor();
    logf("ColorHsl set to ColorHsl(h=%u, s=%u, l=%u)", colorHsl.hue, colorHsl.saturation, colorHsl.value);
    logf("Color set to Color(r=%u, g=%u, b=%u)", currentColor.r, currentColor.g, currentColor.b);
  }
}