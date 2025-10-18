#include "engine/engine.h"
#include "games/testing-sandbox/test-player.h"

namespace Engine
{

  GameEngine::GameEngine() : leds{config}, display{controller, state}
  {
    initializeEngine();
  }

  void GameEngine::runApplication()
  {
    while (state.isRunning())
    {
      if (isReady())
      {
        leds.reset();
        checkChangeRequest();
        display.updateDisplay();

        switch (state.getCurrent())
        {
        case StateOptions::Menu_Home:
          // moving directly to the TestingSandbox game for testing
          // state.setNext(CoreStateOptions::GAME_SANDBOX);
          handleMainMenu();
          break;
        case StateOptions::Game_SandboxTransition:
          initSandbox();
          break;
        case StateOptions::Game_Sandbox:
          game->nextEvent();
          break;
        case StateOptions::NoControllerConnected:
          standbyControllerConnection();
          break;
        default:
          // ideally shouldn't encounter this
          state.setNext(StateOptions::Error);
          break;
        }

        renderLedStrip();
        wait(9); // Targeting a 120Hz refresh rate. 1/120Hz * 1000 gives us 8.3333ms per frame
      }
    }
  }

  void GameEngine::initializeEngine()
  {
    controller.begin(config.macAddress);

    // If debugging, ensure serial connection is stable before setting up components
#if defined(VIRTUALIZATION) || defined(DEBUG)
    Serial.begin(921600);
    log("Connecting to computer using a serial connection for debugging.");
    while (!Serial)
    {
      log("    No Serial connection...");
      delay(100);
    }
    log("Serial connection established.");
#endif

    log("Attempting to connect to PS3 controller");

    // ten second attempt to connect to PS3 controller
    int reattempt = 0;
    while (!controller.isConnected() && reattempt < 80)
    {
      log("    Searching for PS3 controller...");
      ++reattempt;
      delay(250);
    }

    if (!controller.isConnected())
    {
      state.setNext(StateOptions::NoControllerConnected);
      log("Failed to connect to controller. Entering No Controller Connection sequence");
    }
    else
    {
      state.setNext(StateOptions::Menu_Home);
      log("Startup process completed. Transitioning to Main Menu");
    }
  }

  void GameEngine::standbyControllerConnection()
  {
    // while (!controller.isConnected())
    // {
    //   for (int i = 0; i <= leds.size(); ++i)
    //   {
    //     leds.buffer[i].r = 255;
    //     leds.buffer[i].g = 0;
    //     leds.buffer[i].b = 0;
    //   }
    // }
  }

  void GameEngine::checkChangeRequest()
  {
    if (controller.wasPressed(Player::ControllerButton::Ps))
    {
      state.setNext(StateOptions::Menu_Home);
      log("Transitioning to Main Menu.");
    }
  }

  void GameEngine::handleMainMenu()
  {

    if (controller.wasPressed(Player::ControllerButton::Down))
    {
      logf("Highlighting Main Menu option %d", state.getUserMenuChoice());
      state.selectNextMenu();
    }

    if (controller.wasPressed(Player::ControllerButton::Up))
    {
      logf("Highlighting Main Menu option %d", state.getUserMenuChoice());
      state.selectNextMenu(MenuNavigationDirection::Reverse);
    }

    if (controller.wasPressed(Player::ControllerButton::Start) || controller.wasPressed(Player::ControllerButton::Cross))
    {
      state.setNext(StateOptions::Game_Sandbox);
    }
  }

  void GameEngine::initSandbox()
  {
    log("Transitioning to Sandbox game.");
    if (game)
    {
      delete game;
      game = nullptr;
    }
    game = new Games::TestCore{config, leds, controller};
    state.setNext(StateOptions::Game_Sandbox);
  }

  void GameEngine::renderLedStrip()
  {
    leds.adjustLuminance();
#ifdef RELEASE
    // TODO: Add actual logic to send signal to LEDs. Below is a simulation only

    ////// do NOT include this in the final build obviously, this is for testing purposes only /////
    Serial.println("LED strip updated.");
    ////////////////////////////////////////////////////////////////////////////////////////////////
#endif
#ifdef VIRTUALIZATION
    Serial.write(0xAA); // sync bytes
    Serial.write(0x55);
    Serial.write(reinterpret_cast<uint8_t *>(leds.getRawColors()), leds.size() * sizeof(CRGB));
#endif
  }
}