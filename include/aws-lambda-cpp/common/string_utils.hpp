#pragma once

#include <string>
#include <memory>

namespace aws_lambda_cpp {
  namespace common {
    template<typename... Args>
    std::string str_format(const std::string& format, Args... args) {
      auto s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
      if (s <= 0) {
        throw std::runtime_error("Error occurred during string formatting!");
      }
      std::unique_ptr<char[]> buf(new char[s]);
      std::snprintf(buf.get(), s, format.c_str(), args...);
      return std::string(buf.get(), buf.get() + s - 1);
    }

    void replace_all(std::string& str, const std::string& from, const std::string& to);
  }
}

