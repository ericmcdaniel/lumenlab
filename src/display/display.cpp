#include <Wire.h>
#include "display/display.h"

namespace Display
{
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
  }
}