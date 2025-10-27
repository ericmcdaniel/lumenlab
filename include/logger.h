#pragma once

#include <Arduino.h>

/*
  Interesting compiler optimization below, when building with the DEBUG flag
  on it prints to the serial monitor as normal, but when building in RELEASE
  mode (optimization is set to Os), then the do-while loop has zero executions,
  so the entire call to log/logf is removed. Same for the VIRTUALIZATION build,
  which doesn't need those logs in the terminal
*/

#ifdef DEBUG

#define log(msg) Serial.printf("[%lu] [%s] - %s\n", millis(), __PRETTY_FUNCTION__, msg);
#define logf(fmt, ...) Serial.printf("[%lu] [%s] - " fmt "\n", millis(), __PRETTY_FUNCTION__, ##__VA_ARGS__);

#else

#define log(msg) \
  do             \
  {              \
  } while (0)
#define logf(fmt, ...) \
  do                   \
  {                    \
  } while (0)

#endif
