#pragma once

#include <cstdint>

template <typename T, uint16_t N>
constexpr uint16_t arraySize(const T (&)[N]) { return N; }
