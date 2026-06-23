#pragma once

#ifdef VIRTUALIZATION

namespace Display
{
  // Send OLED text update to serial port (only if content changed)
  // Format: 0xBB 0x66 [2-byte length] [text data]
  void sendOledUpdate(const char *text);
  void serializeOledText(const char *text);
}

#endif
