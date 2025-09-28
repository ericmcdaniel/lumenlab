#include <Arduino.h>

#include "display/navigation-controller.h"

namespace Display
{
  NavigationController::NavigationController()
  {
    instance = this;
    pinMode(32, INPUT);
    pinMode(33, INPUT);
    pinMode(21, INPUT);
    pinMode(35, INPUT);
    pinMode(27, INPUT);

    attachInterrupt(digitalPinToInterrupt(32), NavigationController::handleUpButtonPressInterrupt, FALLING);
    attachInterrupt(digitalPinToInterrupt(33), NavigationController::handleDownButtonPressInterrupt, FALLING);
    attachInterrupt(digitalPinToInterrupt(21), NavigationController::handleLeftButtonPressInterrupt, FALLING);
    attachInterrupt(digitalPinToInterrupt(35), NavigationController::handleRightButtonPressInterrupt, FALLING);
    attachInterrupt(digitalPinToInterrupt(27), NavigationController::handlePushButtonPressInterrupt, FALLING);
  }

  void IRAM_ATTR NavigationController::handleUpButtonPress() { navButtonState = NAV_UP; }
  void IRAM_ATTR NavigationController::handleDownButtonPress() { navButtonState = NAV_DOWN; }
  void IRAM_ATTR NavigationController::handleLeftButtonPress() { navButtonState = NAV_LEFT; }
  void IRAM_ATTR NavigationController::handleRightButtonPress() { navButtonState = NAV_RIGHT; }
  void IRAM_ATTR NavigationController::handlePushButtonPress() { navButtonState = NAV_PUSH; }

  void IRAM_ATTR NavigationController::handleUpButtonPressInterrupt()
  {
    if (instance)
      instance->NavigationController::handleUpButtonPress();
  }
  void IRAM_ATTR NavigationController::handleDownButtonPressInterrupt()
  {
    if (instance)
      instance->NavigationController::handleDownButtonPress();
  }
  void IRAM_ATTR NavigationController::handleLeftButtonPressInterrupt()
  {
    if (instance)
      instance->NavigationController::handleLeftButtonPress();
  }
  void IRAM_ATTR NavigationController::handleRightButtonPressInterrupt()
  {
    if (instance)
      instance->NavigationController::handleRightButtonPress();
  }
  void IRAM_ATTR NavigationController::handlePushButtonPressInterrupt()
  {
    if (instance)
      instance->handlePushButtonPress();
  }

  NavigationController *NavigationController::instance = nullptr;
}