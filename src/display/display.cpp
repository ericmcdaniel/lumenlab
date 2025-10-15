#include <Wire.h>

#include "display/display.h"
#include "logger.h"

namespace Display
{
  void OledDisplay::updateDisplay()
  {
    if (isReady())
    {
      switch (state.getCurrent())
      {
      case StateOptions::BootScreen:
        drawBootScreen();
        break;
      case StateOptions::MenuHome:
        drawMainMenu();
        break;
      default:
        drawBootScreen();
        break;
      }
    }
  }

  void OledDisplay::drawBootScreen()
  {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(30, 0);
    display.print("LumenLab v1");
    display.drawBitmap(initLogo.xPos, initLogo.yPos, initLogo.rawValues, initLogo.width, initLogo.height, WHITE);
    display.display();
  }

  void OledDisplay::drawHeader(const char *message)
  {
  }

  void OledDisplay::drawLogo()
  {
  }

  void OledDisplay::drawMainMenu()
  {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(30, 0);
    display.print("Main Menu");

    display.display();
  }

  // void OledDisplay::checkNavMenuChangeRequest()
  // {
  // if (navigationController.navButtonState != NAV_UNPRESSED)
  // {
  //   NavControllerDirection direction = navigationController.navButtonState;
  //   navigationController.navButtonState = NAV_UNPRESSED;

  //   switch (direction)
  //   {
  //   case NAV_UP:
  //     log("Up pressed");
  //     break;
  //   case NAV_DOWN:
  //     log("Down pressed");
  //     break;
  //   case NAV_LEFT:
  //     log("Left pressed");
  //     break;
  //   case NAV_RIGHT:
  //     log("Right pressed");
  //     break;
  //   case NAV_PUSH:
  //     log("Center pressed");
  //     break;
  //   default:
  //     break;
  //   }
  // }
  // }
}