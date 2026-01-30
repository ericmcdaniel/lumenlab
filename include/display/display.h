#pragma once

#include <Adafruit_SSD1306.h>

#ifdef BLACK
#undef BLACK
#endif
#ifdef WHITE
#undef WHITE
#endif

#include "display/display-images.h"

namespace SystemCore
{
  // forward declaration because of ContextManager/OledDisplay circular dependency
  class ContextManager;
}

namespace Display
{

  class OledDisplay
  {
  public:
    OledDisplay(SystemCore::ContextManager *contextManager);
    void updateDisplay();

  private:
    static constexpr int DISPLAY_WIDTH = 128; // The screen holds up to 21 characters, 6 pixels wide
    static constexpr int DISPLAY_HEIGHT = 64; // Characters are 7 pixels tall at minimum
    static constexpr int DISPLAY_ADDRESS = 0x3c;
    Adafruit_SSD1306 display;

    SystemCore::ContextManager *contextManager;
    ImageInitLogo initLogo;

    char selectedOption(uint8_t index, uint8_t selectedOptionIndex) { return index == selectedOptionIndex ? '>' : ' '; };
    int16_t calculateCenterText(const char *text);

    void drawLogo();
    void drawHeader(const char *message);
    void drawBootScreen();
    void drawMainMenu();
    void drawGamesMenu();
    void drawScenesMenu();
    void drawRecallGameHud();
    void drawPhaseEvasionGameHud();
    void drawDemoGameHud();
    void drawCanvasSceneHud();
    void drawUnconnectedControllerScreen();
    void clearDisplay();
  };
}