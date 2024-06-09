#include "lambda/logger.hpp"

using namespace lambda;
using namespace Aws::Utils::Logging;

lambda::logger::logger(const char* tag) {
  this->tag = tag;
}
