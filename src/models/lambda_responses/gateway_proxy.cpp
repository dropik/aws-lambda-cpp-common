#include <aws-lambda-cpp/models/lambda_responses/gateway_proxy.hpp>

#include <aws/core/utils/Array.h>
#include <aws/core/utils/base64/Base64.h>

void aws_lambda_cpp::models::lambda_responses::base_gateway_proxy_response::set_body(const std::string& body, bool encoded) {
  Aws::Utils::Base64::Base64 base64;
  if (!encoded) {
    this->body = body;
    is_base64_encoded = false;
  } else {
    Aws::Utils::Array<unsigned char> buf((unsigned char*)body.c_str(), body.size());
    this->body = base64.Encode(buf);
    is_base64_encoded = true;
  }
}

