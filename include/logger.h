#pragma once

#include <Arduino.h>

#ifdef DEBUG
#define log(msg)                                                            \
  do                                                                        \
  {                                                                         \
    Serial.printf("[%lu] [%s] - %s\n", millis(), __PRETTY_FUNCTION__, msg); \
  } while (0)

#define logf(fmt, ...)                                                                     \
  do                                                                                       \
  {                                                                                        \
    Serial.printf("[%lu] [%s] - " fmt "\n", millis(), __PRETTY_FUNCTION__, ##__VA_ARGS__); \
  } while (0)
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
