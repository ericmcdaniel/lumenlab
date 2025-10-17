#include <Wire.h>

#include "display/display.h"
#include "logger.h"

namespace Display
{
  void OledDisplay::updateDisplay()
  {
    if (isReady())
    {
      // if (engSt.getCurrent() != prevEngSt.getCurrent())
      // {
      //   switch (engSt.getCurrent())
      //   {
      //   case Engine::StateOptions::MainMenu:
      //     logf("Changing to Menu Home");
      //     state.setNext(StateOptions::MenuHome);
      //     break;
      //   default:
      //     state.setNext(StateOptions::BootScreen);
      //     break;
      //   }
      //   prevEngSt.setNext(engSt.getCurrent());
      // }

      switch (engineState.getCurrent())
      {
      case Engine::StateOptions::Initialize:
        drawBootScreen();
        break;
      case Engine::StateOptions::MenuHome:
        drawMainMenu();
        break;
      default:
        drawBootScreen();
        break;
      }
      wait(500);
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

    display.setCursor(0, 8);
    display.print("> Games");
    display.setCursor(0, 16);
    display.print("  Scenes");
    display.setCursor(0, 24);
    display.print("  Ambient");

    display.display();
  }

  // void OledDisplay::checkNavMenuChangeRequest()
  // {
  // if (navigationController.navButtonState != NAV_UNPRESSED)
  // {
  //   NavControllerDirection direction = navigationController.navButtonState;
  //   navigationController.navButtonState = NAV_UNPRESSED;

  //   switch (direction)
  //   {
  //   case NAV_UP:
  //     log("Up pressed");
  //     break;
  //   case NAV_DOWN:
  //     log("Down pressed");
  //     break;
  //   case NAV_LEFT:
  //     log("Left pressed");
  //     break;
  //   case NAV_RIGHT:
  //     log("Right pressed");
  //     break;
  //   case NAV_PUSH:
  //     log("Center pressed");
  //     break;
  //   default:
  //     break;
  //   }
  // }
  // }
}