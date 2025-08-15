#include <Arduino.h>

#include <Ps3Controller.h>

#include "Controller.h"

int player = 0;
int battery = 0;

Controller controller;

void notify()
{
  controller.update_state();
  //--- Digital cross/square/triangle/circle button events ---
  // if (Ps3.event.button_down.cross)
  //   Serial.println("Started pressing the cross button");
  // if (Ps3.event.button_up.cross)
  //   Serial.println("Released the cross button");

  // if (Ps3.event.button_down.square)
  //   Serial.println("Started pressing the square button");
  // if (Ps3.event.button_up.square)
  //   Serial.println("Released the square button");

  // if (Ps3.event.button_down.triangle)
  //   Serial.println("Started pressing the triangle button");
  // if (Ps3.event.button_up.triangle)
  //   Serial.println("Released the triangle button");

  // if (Ps3.event.button_down.circle)
  //   Serial.println("Started pressing the circle button");
  // if (Ps3.event.button_up.circle)
  //   Serial.println("Released the circle button");

  // //--------------- Digital D-pad button events --------------
  // if (Ps3.event.button_down.up)
  //   Serial.println("Started pressing the up button");
  // if (Ps3.event.button_up.up)
  //   Serial.println("Released the up button");

  // if (Ps3.event.button_down.right)
  //   Serial.println("Started pressing the right button");
  // if (Ps3.event.button_up.right)
  //   Serial.println("Released the right button");

  // if (Ps3.event.button_down.down)
  //   Serial.println("Started pressing the down button");
  // if (Ps3.event.button_up.down)
  //   Serial.println("Released the down button");

  // if (Ps3.event.button_down.left)
  //   Serial.println("Started pressing the left button");
  // if (Ps3.event.button_up.left)
  //   Serial.println("Released the left button");

  // //------------- Digital shoulder button events -------------
  // if (Ps3.event.button_down.l1)
  //   Serial.println("Started pressing the left shoulder button");
  // if (Ps3.event.button_up.l1)
  //   Serial.println("Released the left shoulder button");

  // if (Ps3.event.button_down.r1)
  //   Serial.println("Started pressing the right shoulder button");
  // if (Ps3.event.button_up.r1)
  //   Serial.println("Released the right shoulder button");

  // //-------------- Digital trigger button events -------------
  // if (Ps3.event.button_down.l2)
  //   Serial.println("Started pressing the left trigger button");
  // if (Ps3.event.button_up.l2)
  //   Serial.println("Released the left trigger button");

  // if (Ps3.event.button_down.r2)
  //   Serial.println("Started pressing the right trigger button");
  // if (Ps3.event.button_up.r2)
  //   Serial.println("Released the right trigger button");

  // //--------------- Digital stick button events --------------
  // if (Ps3.event.button_down.l3)
  //   Serial.println("Started pressing the left stick button");
  // if (Ps3.event.button_up.l3)
  //   Serial.println("Released the left stick button");

  // if (Ps3.event.button_down.r3)
  //   Serial.println("Started pressing the right stick button");
  // if (Ps3.event.button_up.r3)
  //   Serial.println("Released the right stick button");

  // //---------- Digital select/start/ps button events ---------
  // if (Ps3.event.button_down.select)
  //   Serial.println("Started pressing the select button");
  // if (Ps3.event.button_up.select)
  //   Serial.println("Released the select button");

  // if (Ps3.event.button_down.start)
  //   Serial.println("Started pressing the start button");
  // if (Ps3.event.button_up.start)
  //   Serial.println("Released the start button");

  // if (Ps3.event.button_down.ps)
  //   Serial.println("Started pressing the Playstation button");
  // if (Ps3.event.button_up.ps)
  //   Serial.println("Released the Playstation button");

  // //---------------- Analog stick value events ---------------
  // if (abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2)
  // {
  //   Serial.print("Moved the left stick:");
  //   Serial.print(" x=");
  //   Serial.print(Ps3.data.analog.stick.lx, DEC);
  //   Serial.print(" y=");
  //   Serial.print(Ps3.data.analog.stick.ly, DEC);
  //   Serial.println();
  // }

  // if (abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2)
  // {
  //   Serial.print("Moved the right stick:");
  //   Serial.print(" x=");
  //   Serial.print(Ps3.data.analog.stick.rx, DEC);
  //   Serial.print(" y=");
  //   Serial.print(Ps3.data.analog.stick.ry, DEC);
  //   Serial.println();
  // }

  // //--------------- Analog D-pad button events ----------------
  // if (abs(Ps3.event.analog_changed.button.up))
  // {
  //   Serial.print("Pressing the up button: ");
  //   Serial.println(Ps3.data.analog.button.up, DEC);
  // }

  // if (abs(Ps3.event.analog_changed.button.right))
  // {
  //   Serial.print("Pressing the right button: ");
  //   Serial.println(Ps3.data.analog.button.right, DEC);
  // }

  // if (abs(Ps3.event.analog_changed.button.down))
  // {
  //   Serial.print("Pressing the down button: ");
  //   Serial.println(Ps3.data.analog.button.down, DEC);
  // }

  // if (abs(Ps3.event.analog_changed.button.left))
  // {
  //   Serial.print("Pressing the left button: ");
  //   Serial.println(Ps3.data.analog.button.left, DEC);
  // }

  // //---------- Analog shoulder/trigger button events ----------
  // if (abs(Ps3.event.analog_changed.button.l1))
  // {
  //   Serial.print("Pressing the left shoulder button: ");
  //   Serial.println(Ps3.data.analog.button.l1, DEC);
  // }

  // if (abs(Ps3.event.analog_changed.button.r1))
  // {
  //   Serial.print("Pressing the right shoulder button: ");
  //   Serial.println(Ps3.data.analog.button.r1, DEC);
  // }

  // if (abs(Ps3.event.analog_changed.button.l2))
  // {
  //   Serial.print("Pressing the left trigger button: ");
  //   Serial.println(Ps3.data.analog.button.l2, DEC);
  // }

  // if (abs(Ps3.event.analog_changed.button.r2))
  // {
  //   Serial.print("Pressing the right trigger button: ");
  //   Serial.println(Ps3.data.analog.button.r2, DEC);
  // }

  // //---- Analog cross/square/triangle/circle button events ----
  // if (abs(Ps3.event.analog_changed.button.triangle))
  // {
  //   Serial.print("Pressing the triangle button: ");
  //   Serial.println(Ps3.data.analog.button.triangle, DEC);
  // }

  // if (abs(Ps3.event.analog_changed.button.circle))
  // {
  //   Serial.print("Pressing the circle button: ");
  //   Serial.println(Ps3.data.analog.button.circle, DEC);
  // }

  // if (abs(Ps3.event.analog_changed.button.cross))
  // {
  //   Serial.print("Pressing the cross button: ");
  //   Serial.println(Ps3.data.analog.button.cross, DEC);
  // }

  // if (abs(Ps3.event.analog_changed.button.square))
  // {
  //   Serial.print("Pressing the square button: ");
  //   Serial.println(Ps3.data.analog.button.square, DEC);
  // }

  // //---------------------- Battery events ---------------------
  // if (battery != Ps3.data.status.battery)
  // {
  //   battery = Ps3.data.status.battery;
  //   Serial.print("The controller battery is ");
  //   if (battery == ps3_status_battery_charging)
  //     Serial.println("charging");
  //   else if (battery == ps3_status_battery_full)
  //     Serial.println("FULL");
  //   else if (battery == ps3_status_battery_high)
  //     Serial.println("HIGH");
  //   else if (battery == ps3_status_battery_low)
  //     Serial.println("LOW");
  //   else if (battery == ps3_status_battery_dying)
  //     Serial.println("DYING");
  //   else if (battery == ps3_status_battery_shutdown)
  //     Serial.println("SHUTDOWN");
  //   else
  //     Serial.println("UNDEFINED");
  // }
}

void onConnect()
{
  Serial.println("Connected.");
}

uint8_t ledBuffer[300 * 3 + 2]; // 2 sync bytes + 900 bytes RGB

int count = 0;
int revolution = 0;

void setup()
{
  delay(1000); // allow bootloader and USB to settle
  // Native USB Serial on ESP32-S3
  Serial.begin(921600); // You can increase later, e.g., 921600, but start safe
  Serial.print("Connecting.");
  while (!Serial)
  {
    Serial.print(".");
    delay(100);
  }

  pinMode(BUILTIN_LED, OUTPUT);
  Serial.println("\nUSB LED data sender ready.");

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  // Ps3.attachOnDisconnect();
  Ps3.begin("00:1b:fb:8e:87:ac");

  Serial.println("Ready.");
}

void loop()
{
  // First two bytes are sync markers
  ledBuffer[0] = 0xAA;
  ledBuffer[1] = 0x55;

  // Fill LED buffer
  for (int i = 0; i < 300; i++)
  {
    int base = i * 3 + 2;
    if (i == count && controller.cross())
    {
      ledBuffer[base + 0] = 255; // R
      ledBuffer[base + 1] = 0;   // G
      ledBuffer[base + 2] = 0;   // B
    }
    else
    {
      ledBuffer[base + 0] = 0;
      ledBuffer[base + 1] = 0;
      ledBuffer[base + 2] = 0;
    }
  }

  count = (count + 2) % 300;

  // Send LED buffer over USB Serial
  Serial.write(ledBuffer, sizeof(ledBuffer));
  Serial.flush(); // Ensure data is pushed out
}
