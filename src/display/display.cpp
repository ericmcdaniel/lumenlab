#include <Wire.h>
#include "display/display.h"

namespace Display
{
  void OledDisplay::initialize()
  {
    display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
    Wire.begin();

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("LumenLab");
    display.setCursor(0, 10);
    display.print("Version: 1");
    display.setCursor(0, 20);
    display.display();
  }
}