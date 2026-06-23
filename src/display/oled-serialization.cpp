#ifdef VIRTUALIZATION

#include <cstring>
#include <Arduino.h>
#include "display/oled-serialization.h"

namespace Display
{
  static uint32_t simpleHash(const char *str)
  {
    uint32_t hash = 5381;
    int c;
    while ((c = *str++))
      hash = ((hash << 5) + hash) + c;
    return hash;
  }

  static uint32_t previousHash = 0;

  void serializeOledText(const char *text)
  {
    if (!text)
      return;

    size_t len = strlen(text);
    if (len > 65535)
      len = 65535;

    Serial.write(0xBB);
    Serial.write(0x66);
    Serial.write((uint8_t)(len >> 8));
    Serial.write((uint8_t)(len & 0xFF));

    Serial.write(reinterpret_cast<const uint8_t *>(text), len);
  }

  void sendOledUpdate(const char *text)
  {
    if (!text)
      return;

    uint32_t currentHash = simpleHash(text);

    if (currentHash != previousHash)
    {
      previousHash = currentHash;
      serializeOledText(text);
    }
  }
}

#endif
