#pragma once

#include <Adafruit_SSD1306.h>

#include "engine/timer.h"
#include "engine/state-manager.h"
#include "display/display-images.h"
#include "player/controller.h"

namespace Display
{

  class OledDisplay
  {
  private:
    static constexpr int DISPLAY_WIDTH = 128;
    static constexpr int DISPLAY_HEIGHT = 64;
    static constexpr int OLED_RESET = 4;
    static constexpr int DISPLAY_ADDRESS = 0x3c;
    Adafruit_SSD1306 display;

    Engine::StateManager &engineState;
    ImageInitLogo initLogo;
    Player::Controller &controller;

    char selectedOption(uint8_t index, uint8_t selectedOptionIndex) { return index == selectedOptionIndex ? '>' : ' '; };
    int16_t calculateCenterText(const char *text);

    void drawLogo();
    void drawHeader(const char *message);
    void drawBootScreen();
    void drawMainMenu();
    void drawGamesMenu();
    void drawUnconnectedControllerScreen();

  public:
    OledDisplay(Player::Controller &c, Engine::StateManager &es);
    void updateDisplay();
  };
}