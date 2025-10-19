#include <Wire.h>

#include "display/display.h"
#include "logger.h"

namespace Display
{

  OledDisplay::OledDisplay(Player::Controller &c, const Engine::StateManager &es) : display{OLED_RESET}, controller{c}, engineState{es}
  {
    Wire.begin();
    display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    drawBootScreen();
  }

  void OledDisplay::updateDisplay()
  {
    if (hasUpdates)
    {
      switch (engineState.getCurrent())
      {
      case Engine::StateOptions::Initialize:
        drawBootScreen();
        break;
      case Engine::StateOptions::Menu_Home:
        drawMainMenu();
        break;
      case Engine::StateOptions::Menu_Games:
        drawGamesMenu();
        break;
      default:
        drawBootScreen();
        break;
      }
      hasUpdates = false;
    }
  }

  int16_t OledDisplay::calculateCenterText(const char *text)
  {
    // unitialized but mutated by the Adafruit library
    int16_t textStartX, textStartY;
    uint16_t textWidth, textHeight;

    display.getTextBounds(text, 0, 0, &textStartX, &textStartY, &textWidth, &textHeight);

    int16_t centeredX = (DISPLAY_WIDTH - textWidth) / 2;
    return centeredX;
  }

  void OledDisplay::drawHeader(const char *message)
  {
    auto startingX = calculateCenterText(message);
    display.setCursor(startingX, 0);
    display.print(message);
  }

  void OledDisplay::drawLogo()
  {
  }

  void OledDisplay::drawBootScreen()
  {
    display.clearDisplay();
    drawHeader("LumenLab v1");

    display.drawBitmap(initLogo.xPos, initLogo.yPos, initLogo.rawValues, initLogo.width, initLogo.height, WHITE);
    display.display();
  }

  void OledDisplay::drawMainMenu()
  {
    display.clearDisplay();
    drawHeader("Main Menu");

    uint8_t selectedOptionIndex = static_cast<uint8_t>(engineState.getUserMenuChoice());

    display.setTextSize(1);
    display.setCursor(0, 8);
    display.print(selectedOption(0, selectedOptionIndex));
    display.print("  Games");
    display.setCursor(0, 16);
    display.print(selectedOption(1, selectedOptionIndex));
    display.print("  Scenes");

    display.display();
  }

  void OledDisplay::drawGamesMenu()
  {
    display.clearDisplay();
    drawHeader("Games Menu");

    uint8_t selectedOptionIndex = static_cast<uint8_t>(engineState.getUserGameChoice());

    display.setTextSize(1);
    display.setCursor(0, 8);
    display.print(selectedOption(0, selectedOptionIndex));
    display.print("  Sandbox (Testing)");
    display.setCursor(0, 16);
    display.print(selectedOption(1, selectedOptionIndex));
    display.print("  Recall");
    display.setCursor(0, 24);
    display.print(selectedOption(2, selectedOptionIndex));
    display.print("  Phase Evasion");

    display.display();
  }
}