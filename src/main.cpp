#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#undef min
#undef max

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup()
{
  pinMode(2, OUTPUT);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

int counter = 0;

void loop()
{

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Test Example");
  display.setCursor(0, 10);
  display.print("Counter:    ");
  display.print(counter++);
  display.print(" %");
  display.setCursor(0, 20);
  display.print("Temperature: ");
  display.print(69);
  display.print(" C");
  display.display();

  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(500);
}
