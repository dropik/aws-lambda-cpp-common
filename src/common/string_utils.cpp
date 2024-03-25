#include <cstdarg>
#include <cstdio>
#include <memory>
#include <stdexcept>

#include "common/string_utils.hpp"

using namespace aws_lambda_cpp::common;

std::string aws_lambda_cpp::common::str_format_var(const char *format, ...) {
  va_list args;
  va_start(args, format);
  std::string res = str_format_var(format, args);
  va_end(args);
  return res;
}

std::string aws_lambda_cpp::common::str_format_var(const char *format, std::va_list args) {
  int s = std::vsnprintf(nullptr, 0, format, args) + 1;
  if (s <= 0) {
    throw std::runtime_error("Error occured during string formatting!");
  }
  size_t size = static_cast<size_t>(s);
  std::unique_ptr<char[]> buf(new char[size]);
  std::vsnprintf(buf.get(), size, format, args);
  return std::string(buf.get(), buf.get() + size - 1);
}

