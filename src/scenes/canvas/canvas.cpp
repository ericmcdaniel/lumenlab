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
    // switch (state.current)
    // {

    // }
    // check
    for (uint16_t i; i < contextManager->leds.size(); ++i)
    {
      contextManager->leds.buffer[i] = colorHsl.toColor();
    }
    Lights::Color c = colorHsl.toColor();
  }

  void Canvas::checkColorChange()
  {
    // contextManager->controller.
  }

  void Canvas::reset()
  {
    colorHsl.hue() = static_cast<uint8_t>(esp_random() % std::numeric_limits<uint8_t>::max());
    colorHsl.saturation() = static_cast<uint8_t>(esp_random() % std::numeric_limits<uint8_t>::max());
    colorHsl.lightness() = static_cast<uint8_t>(esp_random() % std::numeric_limits<uint8_t>::max());
    Lights::Color c = colorHsl.toColor();
    logf("Color set to Color(r=%u, g=%u, b=%u)", c.r, c.g, c.b);
  }
}