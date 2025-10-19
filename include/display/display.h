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
    static constexpr int DISPLAY_WIDTH = 128; // The screen holds up to 21 characters, 6 pixels wide
    static constexpr int DISPLAY_HEIGHT = 64; // Characters are 7 pixels tall at minimum
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
    void drawTransitionScreen(const char *name);
    void drawSandboxGameHud();
    void drawUnconnectedControllerScreen();

  public:
    OledDisplay(Player::Controller &c, Engine::StateManager &es);
    void updateDisplay();
  };
}