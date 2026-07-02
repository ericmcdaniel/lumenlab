#pragma once

namespace CustomDataStructures
{
  template <typename T>
  class Span
  {
  public:
    constexpr Span(const T *data, uint16_t size) : data_(data), size_(size) {}

    constexpr const T &operator[](uint16_t i) const { return data_[i]; }

    constexpr const T *begin() const { return data_; }
    constexpr const T *end() const { return data_ + size_; }

    constexpr uint16_t size() const { return size_; }

  private:
    const T *data_;
    uint16_t size_;
  };
}
