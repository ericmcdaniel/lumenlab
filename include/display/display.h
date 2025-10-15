#pragma once

#include <Adafruit_SSD1306.h>

#include "display/display-images.h"
#include "player/controller.h"

namespace Display
{

  class OledDisplay
  {
  private:
    static constexpr int OLED_RESET = 4;
    static constexpr int DISPLAY_ADDRESS = 0x3c;
    Adafruit_SSD1306 display;
    ImageInitLogo initLogo;
    Player::Controller &controller;
    void printLogo();

  public:
    OledDisplay(Player::Controller &c) : display(OLED_RESET), controller{c}
    {
      initialize();
    }
    void initialize();
    void displayHeader(const char *message);
    void checkNavMenuChangeRequest();
  };
}