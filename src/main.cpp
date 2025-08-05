#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "secrets.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

const char *clientIpAddress = CLIENT_IP_ADDRESS;
const int clientPort = CLIENT_PORT;

uint8_t ledBuffer[300 * 3] = {0};

WiFiUDP udp;

void setup()
{
  Serial.begin(SERIAL_BAUD);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  pinMode(BUILTIN_LED, OUTPUT);
}

int count = 0;

void loop()
{
  digitalWrite(BUILTIN_LED, HIGH);
  Serial.println("On.");
  delay(250);

  digitalWrite(BUILTIN_LED, LOW);
  Serial.println("Off.");

  for (int i = 0; i < 300; i++)
  {
    int base = i * 3;
    ledBuffer[base + 0] = count % 3 == 0 ? 255 : 0;
    ledBuffer[base + 1] = count % 3 == 1 ? 255 : 0;
    ledBuffer[base + 2] = count % 3 == 2 ? 255 : 0;
  }
  count++;

  Serial.printf("Sending %d bytes to %s:%d\n", sizeof(ledBuffer), clientIpAddress, clientPort);

  if (udp.beginPacket(clientIpAddress, clientPort))
  {
    int written = udp.write(ledBuffer, sizeof(ledBuffer));
    udp.endPacket();
    Serial.printf("Wrote %d bytes\n", written);
  }
  else
  {
    Serial.println("Failed to begin UDP packet");
  }

  Serial.println("UDP packet sent");

  delay(200);
}
