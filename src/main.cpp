#include <Arduino.h>

uint8_t ledBuffer[300 * 3 + 2]; // 2 sync bytes + 900 bytes RGB

int count = 0;
int revolution = 0;

void setup()
{
  delay(1000); // allow bootloader and USB to settle
  // Native USB Serial on ESP32-S3
  Serial.begin(115200); // You can increase later, e.g., 921600, but start safe
  Serial.print("Connecting.");
  while (!Serial)
  {
    Serial.print(".");
    delay(100);
  }

  pinMode(BUILTIN_LED, OUTPUT);

  Serial.println("\nUSB LED data sender ready.");
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
    if (i == count)
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
