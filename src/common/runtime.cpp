#include <aws-lambda-cpp/common/runtime.hpp>
#include <cstring>
#include <iostream>

using namespace aws_lambda_cpp::runtime;

bool debug = false;
std::string payload;

bool aws_lambda_cpp::runtime::is_debug() {
  return debug;
}

void aws_lambda_cpp::runtime::set_debug(int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
	if (strcmp(argv[i], "--debug") == 0) {
	  debug = true;
	}
  }
}

void aws_lambda_cpp::runtime::load_inline_payload()
{
  if (debug) {
	std::string line;
	while (std::getline(std::cin, line)) {
	  payload += line;
	}
  }
}

void aws_lambda_cpp::runtime::run_debug(std::function<aws::lambda_runtime::invocation_response(const aws::lambda_runtime::invocation_request&)> handler)
{
  if (debug) {
	aws::lambda_runtime::invocation_request req;
	req.payload = payload;
	aws::lambda_runtime::invocation_response res = handler(req);
	std::cout << "--- Response ---" << std::endl;
	std::cout << res.get_payload() << std::endl;
	std::cout << "--- End Response ---" << std::endl;
  }
  else {
	run_handler(handler);
  }
}
