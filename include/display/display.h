#pragma once
#include <Adafruit_SSD1306.h>

namespace Display
{

  class OledDisplay
  {
  private:
    static constexpr int OLED_RESET = 4;
    static constexpr int DISPLAY_ADDRESS = 0x3c;
    Adafruit_SSD1306 display;

  public:
    OledDisplay() : display(OLED_RESET)
    {
      initialize();
    }
    void initialize();
  };
}