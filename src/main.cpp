#include <Arduino.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting esp32 up.");
  pinMode(BUILTIN_LED, OUTPUT);
}

void loop()
{
  digitalWrite(BUILTIN_LED, HIGH);
  Serial.println("On.");
  delay(100);

  digitalWrite(BUILTIN_LED, LOW);
  Serial.println("Off.");
  delay(100);
}
