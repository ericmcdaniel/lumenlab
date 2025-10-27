#include <Wire.h>

#include "display/display.h"
#include "core/context-manager.h"
#include "logger.h"

namespace Display
{
  OledDisplay::OledDisplay(Core::ContextManager *ctx) : contextManager{ctx}
  {
    Wire.begin();
    display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    drawBootScreen();
  }

  void OledDisplay::updateDisplay()
  {
    if (contextManager->stateManager.displayShouldUpdate)
    {
      switch (contextManager->stateManager.getCurrent())
      {
      case Engine::SystemState::Initialize:
        drawBootScreen();
        break;
      case Engine::SystemState::MenuHome:
        drawMainMenu();
        break;
      case Engine::SystemState::MenuGames:
        drawGamesMenu();
        break;
      case Engine::SystemState::GameSandbox:
        drawSandboxGameHud();
        break;
      case Engine::SystemState::GameRecall:
        drawRecallGameHud();
        break;
      case Engine::SystemState::NoControllerConnected:
        drawUnconnectedControllerScreen();
        break;
      default:
        drawBootScreen();
        break;
      }
      contextManager->stateManager.displayShouldUpdate = false;
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
    drawHeader("LumenLab");

    display.drawBitmap(initLogo.xPos, initLogo.yPos, initLogo.rawValues, initLogo.width, initLogo.height, SSD1306_WHITE);
    display.display();
  }

  void OledDisplay::drawMainMenu()
  {
    display.clearDisplay();
    drawHeader("Main Menu");

    uint8_t selectedOptionIndex = static_cast<uint8_t>(contextManager->stateManager.getUserMenuChoice());

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

    uint8_t selectedOptionIndex = static_cast<uint8_t>(contextManager->stateManager.getUserGameChoice());
    char nameBuffer[32] = "";

    display.setCursor(0, 8);
    sprintf(nameBuffer, "%c  %s", selectedOption(0, selectedOptionIndex), contextManager->stateManager.printGameName(0));
    display.print(nameBuffer);

    display.setCursor(0, 16);
    sprintf(nameBuffer, "%c  %s", selectedOption(1, selectedOptionIndex), contextManager->stateManager.printGameName(1));
    display.print(nameBuffer);

    display.setCursor(0, 24);
    sprintf(nameBuffer, "%c  %s", selectedOption(2, selectedOptionIndex), contextManager->stateManager.printGameName(2));
    display.print(nameBuffer);

    display.display();
  }

  void OledDisplay::drawSandboxGameHud()
  {
    display.clearDisplay();
    drawHeader("Sandbox (Testing)");

    display.setCursor(0, 16);
    display.print("Current Score: ");
    display.print(contextManager->stateManager.getSandboxGameState().currentScore);
    display.setCursor(0, 24);
    display.print("High Score: -");

    display.display();
  }

  void OledDisplay::drawRecallGameHud()
  {
    display.clearDisplay();
    drawHeader("Recall");

    display.setCursor(0, 16);
    display.print("Round: ");
    display.print(contextManager->stateManager.getRecallGameState().round + 1);
    display.setCursor(0, 24);
    display.print("High Score: -");

    display.display();
  }

  void OledDisplay::drawUnconnectedControllerScreen()
  {
    display.clearDisplay();
    drawHeader("LumenLab");

    auto startingX = calculateCenterText("PS3 controller");
    display.setCursor(startingX, 8);
    display.print("PS3 controller");
    startingX = calculateCenterText("not connected");
    display.setCursor(startingX, 16);
    display.print("not connected");

    display.display();
  }
}