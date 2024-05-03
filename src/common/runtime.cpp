#include <aws-lambda-cpp/common/runtime.hpp>
#include <cstring>
#include <iostream>
#include <fstream>

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

void aws_lambda_cpp::runtime::load_payload(int argc, char* argv[])
{
  if (debug) {
	// read payload from file provided as -p argument
	for (int i = 1; i < argc; i++) {
	  if (strcmp(argv[i], "-p") == 0) {
		// check if there is a file name provided
		if (i + 1 >= argc) {
		  throw std::runtime_error("No file name provided for payload argument -p");
		}
		// read payload from file
		std::ifstream file(argv[i + 1]);
		std::string str;
		if (file.is_open()) {
		  while (std::getline(file, str))
		  {
			payload += str;
		  }
		  file.close();
		}
		else {
		  throw std::runtime_error("Could not open file: " + std::string(argv[i + 1]));
		}
	  }
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
