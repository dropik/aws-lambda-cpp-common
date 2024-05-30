#include <cstdio>
#include <stdexcept>

#include <aws-lambda-cpp/common/string_utils.hpp>

using namespace aws_lambda_cpp::common;

void aws_lambda_cpp::common::replace_all(std::string& str, const std::string& from, const std::string& to) {
  if(from.empty()) {
    return;
  }
  
  size_t start_pos = 0;
  while((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
  }
}

