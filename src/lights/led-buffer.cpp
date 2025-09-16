#include "lights/led-buffer.h"

namespace Lights
{
  LedBuffer::LedBuffer(unsigned int numLeds) : size{numLeds}
  {
    leds = new CRGB[size];
    for (int i = 0; i < this->size; i++)
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