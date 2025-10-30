#pragma once

#include <cstddef>

template <typename T, size_t N>
constexpr size_t arraySize(const T (&)[N]) { return N; }
