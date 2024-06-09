#include <lambda/models/responses/gateway_proxy.hpp>

#include <aws/core/utils/Array.h>
#include <aws/core/utils/base64/Base64.h>

void lambda::models::responses::base_gateway_proxy_response::set_body(const std::string& new_body, bool encoded) {
  Aws::Utils::Base64::Base64 base64;
  if (!encoded) {
    this->body = new_body;
    is_base64_encoded = false;
  } else {
    Aws::Utils::Array<unsigned char> buf((unsigned char*)new_body.c_str(), new_body.size());
    this->body = base64.Encode(buf);
    is_base64_encoded = true;
  }
}
