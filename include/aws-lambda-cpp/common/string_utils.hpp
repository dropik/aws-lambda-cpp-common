#pragma once

#include <cstdarg>
#include <string>

namespace aws_lambda_cpp {
  namespace common {
    std::string str_format_var(const char* format, ...);
    std::string str_format_var(const char* format, std::va_list args);

    template<typename... Args>
    std::string str_format(const std::string& format, Args... args) {
      return str_format_var(format.c_str(), args...);
    }
  }
}

