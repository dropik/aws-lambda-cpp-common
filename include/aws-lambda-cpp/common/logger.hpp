#pragma once

#include <string>
#include <aws/core/utils/logging/LogLevel.h>

using namespace Aws::Utils::Logging;

namespace aws_lambda_cpp {
  namespace common {

    /*
     * A simple logger based on AWS logger that basically
     * encapsulates tag.
     */
    class logger {
      public:
        logger(const char* tag);

        template<typename... Args>
        void info(const std::string& message, Args... args) const {
          this->log(LogLevel::Info, message.c_str(), args...);
        }
        
        template<typename... Args>
        void warning(const std::string& message, Args... args) const {
          this->log(LogLevel::Warn, message.c_str(), args...);
        }

        template<typename... Args>
        void debug(const std::string& message, Args... args) const {
          this->log(LogLevel::Debug, message.c_str(), args...);
        }

        template<typename... Args>
        void error(const std::string& message, Args... args) const {
          this->log(LogLevel::Error, message.c_str(), args...);
        }
        
        template<typename... Args>
        void fatal(const std::string& message, Args... args) const {
          this->log(LogLevel::Fatal, message.c_str(), args...);
        }
        
        template<typename... Args>
        void trace(const std::string& message, Args... args) const {
          this->log(LogLevel::Trace, message.c_str(), args...);
        }

      private:
        const char* tag;
        void log(LogLevel log_level, const char* message, ...) const;
    };
  }
}

