#pragma once

#include <string>
#include <functional>
#include <aws/lambda-runtime/runtime.h>

namespace lambda {
namespace runtime {

bool is_debug();
void set_debug(int argc, char *argv[]);
void load_payload(int argc, char *argv[]);
void run_debug(std::function<aws::lambda_runtime::invocation_response(
    const aws::lambda_runtime::invocation_request &)> handler);

}
}
