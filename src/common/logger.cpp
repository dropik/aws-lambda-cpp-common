#include <cstdarg>
#include <aws/core/utils/logging/LogMacros.h>

#include <aws-lambda-cpp/common/logger.hpp>
#include <aws-lambda-cpp/common/string_utils.hpp>

using namespace aws_lambda_cpp::common;
using namespace Aws::Utils::Logging;

aws_lambda_cpp::common::logger::logger(const char* tag) {
  this->tag = tag;
}

//void aws_lambda_cpp::common::logger::log(LogLevel log_level, const char* message, ...) const {
//  va_list args;
//  va_start(args, message);
//  AWS_LOGSTREAM(log_level, this->tag, str_format_var(message, args));
//  AWS_LOGSTREAM_FLUSH();
//  va_end(args);
//}

