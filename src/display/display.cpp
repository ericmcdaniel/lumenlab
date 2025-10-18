#include <Wire.h>

#include "display/display.h"
#include "logger.h"

namespace Display
{
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

  void OledDisplay::drawBootScreen()
  {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(30, 0);
    display.print("LumenLab v1");
    display.drawBitmap(initLogo.xPos, initLogo.yPos, initLogo.rawValues, initLogo.width, initLogo.height, WHITE);
    display.display();
  }

  void OledDisplay::drawHeader(const char *message)
  {
  }

  void OledDisplay::drawLogo()
  {
  }

  void OledDisplay::drawMainMenu()
  {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(39, 0);
    display.print("Main Menu");

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
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(38, 0);
    display.print("Games Menu");

    uint8_t selectedOptionIndex = static_cast<uint8_t>(engineState.getUserGameChoice());

    display.setTextSize(1);
    display.setCursor(0, 8);
    display.print(selectedOption(0, selectedOptionIndex));
    display.print("  Sandbox (Testing)");
    display.setCursor(0, 16);
    display.print(selectedOption(1, selectedOptionIndex));
    display.print("  Recall");
    display.setCursor(0, 24);
    display.print(selectedOption(1, selectedOptionIndex));
    display.print("  Phase Evasion");

    display.display();
  }
}