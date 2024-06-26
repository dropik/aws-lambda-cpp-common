#include <aws/core/utils/base64/Base64.h>
#include <string>

#include <lambda/models/payloads/gateway_proxy.hpp>

using namespace Aws::Utils::Base64;

std::string lambda::models::payloads::base_gateway_proxy_request::get_body(bool decoded) const {
  if (!decoded || !this->is_base64_encoded) {
    return this->body;
  }

  Base64 base64;
  auto buf = base64.Decode(this->body);
  unsigned char* u_array = buf.GetUnderlyingData();

  std::string result(u_array, u_array + buf.GetLength());
  return result;
}
