#include <Wire.h>

#include "display/display.h"
#include "logger.h"

namespace Display
{
  void OledDisplay::printLogo()
  {
  }

  void OledDisplay::initialize()
  {
    Wire.begin();
    display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(30, 0);
    display.print("LumenLab v1");

    display.drawBitmap(initLogo.xPos, initLogo.yPos, initLogo.rawValues, initLogo.width, initLogo.height, WHITE);

    display.display();
    delay(1000);
  }

  void OledDisplay::displayHeader(const char *message)
  {
    // display.
  }

  void OledDisplay::processMainMenuControls()
  {
    if (navigationController.navButtonState != NAV_UNPRESSED)
    {
      NavControllerDirection direction = navigationController.navButtonState;
      navigationController.navButtonState = NAV_UNPRESSED;

      switch (direction)
      {
      case NAV_UP:
        log("Up pressed");
        break;
      case NAV_DOWN:
        log("Down pressed");
        break;
      case NAV_LEFT:
        log("Left pressed");
        break;
      case NAV_RIGHT:
        log("Right pressed");
        break;
      case NAV_PUSH:
        log("Center pressed");
        break;
      default:
        break;
      }
    }
  }
}