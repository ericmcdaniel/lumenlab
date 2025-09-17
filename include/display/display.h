#pragma once
#include <Adafruit_SSD1306.h>

namespace Display
{
  constexpr int OLED_RESET = 4;
  constexpr int DISPLAY_ADDRESS = 0x3c;

  class OledDisplay
  {
  private:
    Adafruit_SSD1306 display;

  public:
    OledDisplay() : display(OLED_RESET) {}
    void initialize();
  };
}