#include "lights/led-buffer.h"

namespace Lights
{
  LedBuffer::LedBuffer(unsigned int numLeds) : _size{numLeds}
  {
    leds = new CRGB[_size];
    for (int i = 0; i < _size; i++)
    {
      leds[i].r = 128;
      leds[i].g = 128;
      leds[i].b = 128;
    }
  }

  LedBuffer::~LedBuffer()
  {
    delete leds;
  }
}