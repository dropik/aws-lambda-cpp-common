#pragma once

#include <string>
#include <vector>
#include <map>

#include "lambda/json.hpp"

namespace lambda {
namespace models {
namespace responses {

struct base_gateway_proxy_response {
  bool is_base64_encoded;
  int status_code;
  std::map<std::string, std::string> headers;
  std::map<std::string, std::vector<std::string>> multi_value_headers;
  std::string body;

  void set_body(const std::string &new_body, bool encoded = false);

  JSON_BEGIN_SERIALIZER(base_gateway_proxy_response)
      JSON_PROPERTY("isBase64Encoded", is_base64_encoded)
      JSON_PROPERTY("statusCode", status_code)
      JSON_PROPERTY("headers", headers)
      JSON_PROPERTY("multiValueHeaders", multi_value_headers)
      JSON_PROPERTY("body", body)
  JSON_END_SERIALIZER()
};

template<typename _payloadT>
class gateway_proxy_response : public base_gateway_proxy_response {
 public:
  void set_payload(const _payloadT &payload, bool encoded = false) {
    std::string body = lambda::json::serialize(payload, true);
    this->set_body(body, encoded);
  }
};

}
}
}
