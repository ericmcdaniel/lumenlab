#pragma once

namespace Time
{

  class Timeable
  {
  private:
    unsigned long next;

  public:
    Timeable() = default;
    ~Timeable() = default;

    Timeable(const Timeable &other) : next(other.next) {}
    virtual Timeable &operator=(const Timeable &other)
    {
      next = other.next;
      return *this;
    }

    Timeable(Timeable &&other) noexcept : next(other.next)
    {
      other.next = 0;
    }
    virtual Timeable &operator=(Timeable &&other) noexcept
    {
      next = other.next;
      other.next = 0;
      return *this;
    }

    const bool isReady() const;
  };
}