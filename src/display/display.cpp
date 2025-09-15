#include <Wire.h>
#include "display/display.h"

namespace Display
{
  void OledDisplay::initialize()
  {
    display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
    Wire.begin();
  }
}