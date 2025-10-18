#pragma once

#include <Adafruit_SSD1306.h>

#include "engine/timer.h"
#include "engine/state-manager.h"
#include "display/display-images.h"
#include "player/controller.h"

namespace Display
{

  class OledDisplay : public Engine::Timer
  {
  private:
    static constexpr int OLED_RESET = 4;
    static constexpr int DISPLAY_ADDRESS = 0x3c;
    Adafruit_SSD1306 display;

    const Engine::StateManager &engineState;
    ImageInitLogo initLogo;
    Player::Controller &controller;
    // bool hasUpdates = false;

    void drawLogo();
    void drawHeader(const char *message);
    void drawBootScreen();
    void drawMainMenu();

  public:
    OledDisplay(Player::Controller &c, const Engine::StateManager &es) : Engine::Timer{}, display{OLED_RESET}, controller{c}, engineState{es}
    {
      Wire.begin();
      display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
      drawBootScreen();
    }

    void updateDisplay();
  };
}