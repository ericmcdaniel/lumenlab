#pragma once

namespace Display
{

  enum NavControllerDirection
  {
    NAV_UNPRESSED = 0,
    NAV_UP = 1,
    NAV_DOWN = 2,
    NAV_LEFT = 3,
    NAV_RIGHT = 4,
    NAV_PUSH = 5,
  };

  class NavigationController
  {
  private:
    void IRAM_ATTR handleUpButtonPress();
    void IRAM_ATTR handleDownButtonPress();
    void IRAM_ATTR handleLeftButtonPress();
    void IRAM_ATTR handleRightButtonPress();
    void IRAM_ATTR handlePushButtonPress();

    static void IRAM_ATTR handleUpButtonPressInterrupt();
    static void IRAM_ATTR handleDownButtonPressInterrupt();
    static void IRAM_ATTR handleLeftButtonPressInterrupt();
    static void IRAM_ATTR handleRightButtonPressInterrupt();
    static void IRAM_ATTR handlePushButtonPressInterrupt();
    static NavigationController *instance;

  public:
    NavigationController();
    volatile NavControllerDirection navButtonState = NAV_UNPRESSED;
  };
}