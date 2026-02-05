#include "scenes/canvas/driver.h"
#include "esp_system.h"
#include "logger.h"
#include <limits>

namespace Scenes::Canvas
{

  Driver::Driver(SystemCore::ContextManager *ctx) : contextManager{ctx}
  {
    reset();
  }

  void Driver::nextEvent()
  {
    checkAnalogColorChange();
    checkBalanceColorRequest();
    checkNewColorRequest();
    checkChangeOccured();
    checkStableControllerForDisplay();

    for (uint16_t i; i < contextManager->leds.size(); ++i)
    {
      contextManager->leds.buffer[i] = contextManager->stateManager.getCanvasSceneState().currentColor;
    }
  }

  void Driver::checkAnalogColorChange()
  {
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
      colorHsl.saturation = std::clamp(colorHsl.saturation - 2, 0, 255);
      hasChange = true;
    }
    if (contextManager->controller.leftAnalog().y < -64)
    {
      colorHsl.saturation = std::clamp(colorHsl.saturation + 2, 0, 255);
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
  }

  void Driver::checkNewColorRequest()
  {
    if (contextManager->controller.wasPressed(Player::ControllerButton::Triangle))
    {
      controllerWasActive = true;
      reset();
    }
  }

  void Driver::checkBalanceColorRequest()
  {
    if (contextManager->controller.wasPressed(Player::ControllerButton::L1))
    {
      if (colorHsl.saturation == 255)
        return;
      colorHsl.saturation = 255;
      hasChange = true;
      controllerWasActive = true;
      logf("Rebalancing saturation (s=255)");
    }

    if (contextManager->controller.wasPressed(Player::ControllerButton::R1))
    {
      if (colorHsl.value == 128)
        return;
      colorHsl.value = 128;
      hasChange = true;
      controllerWasActive = true;
      logf("Rebalancing lightness (l=128)");
    }
  }

  void Driver::checkChangeOccured()
  {
    if (hasChange)
    {
      auto &color = contextManager->stateManager.getCanvasSceneState().currentColor;
      color = colorHsl.toColor();
      hasChange = false;
      logf("Color changed to Color(r=%u, g=%u, b=%u)", color.r, color.g, color.b);
    }
  }

  void Driver::checkStableControllerForDisplay()
  {
    bool isMoving =
        abs(contextManager->controller.leftAnalog().x) > 64 ||
        abs(contextManager->controller.leftAnalog().y) > 64 ||
        abs(contextManager->controller.rightAnalog().y) > 64;

    if (isMoving)
    {
      controllerWasActive = true;
      contextManager->stateManager.displayShouldUpdate = false;
    }
    else if (controllerWasActive)
    {
      controllerWasActive = false;
      contextManager->stateManager.displayShouldUpdate = true;
      log("The display was updated");
    }
  }

  void Driver::reset()
  {
    colorHsl.hue = static_cast<uint8_t>(esp_random() % std::numeric_limits<uint8_t>::max());
    colorHsl.saturation = static_cast<uint8_t>((esp_random() % 64u) + 191u);
    colorHsl.value = static_cast<uint8_t>((esp_random() % 64u) + 96u);

    auto &color = contextManager->stateManager.getCanvasSceneState().currentColor;
    color = colorHsl.toColor();
    hasChange = true;

    logf("ColorHsl set to ColorHsl(h=%u, s=%u, l=%u)", colorHsl.hue, colorHsl.saturation, colorHsl.value);
    logf("Color set to Color(r=%u, g=%u, b=%u)", color.r, color.g, color.b);
  }
}