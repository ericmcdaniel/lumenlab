#pragma once

#ifdef DEBUG
#define log(msg)                                                                    \
  do                                                                                \
  {                                                                                 \
    Serial.printf("[DEBUG] [%s] - %lu - %s\n", __PRETTY_FUNCTION__, millis(), msg); \
  } while (0)

#define logf(fmt, ...)                                                                             \
  do                                                                                               \
  {                                                                                                \
    Serial.printf("[DEBUG] [%s] - %lu - " fmt "\n", __PRETTY_FUNCTION__, millis(), ##__VA_ARGS__); \
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
