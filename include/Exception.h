#pragma once

#include <exception>
#include <string>

class InvalidStateException : public std::exception
{
private:
  std::string message;

public:
  InvalidStateException(const std::string &msg) : message(msg) {}

  const char *what() const noexcept override
  {
    return message.c_str();
  }
};