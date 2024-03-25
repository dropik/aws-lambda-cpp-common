#pragma once

#include <string>
#include <map>
#include <vector>

#include "aws-lambda-cpp/common/json.hpp"
#include "aws-lambda-cpp/common/nullable.hpp"

namespace aws_lambda_cpp {
  using namespace aws_lambda_cpp::common;

  namespace models {
    namespace lambda_payloads {
      class gateway_proxy_request_identity {
        public:
          nullable<std::string> cognito_identity_pool_id;
          nullable<std::string> account_id;
          nullable<std::string> cognito_identity_id;
          nullable<std::string> caller;
          nullable<std::string> access_key;
          std::string source_ip = "";
          nullable<std::string> cognito_authentication_type;
          nullable<std::string> cognito_authentication_provider;
          nullable<std::string> user_arn;
          std::string user_agent = "";
          nullable<std::string> user;

          JSON_BEGIN_SERIALIZER(gateway_proxy_request_identity)
            JSON_PROPERTY("cognitoIdentityPoolId", cognito_identity_pool_id)
            JSON_PROPERTY("accountId", account_id)
            JSON_PROPERTY("cognitoIdentityId", cognito_identity_id)
            JSON_PROPERTY("caller", caller)
            JSON_PROPERTY("accessKey", access_key)
            JSON_PROPERTY("sourceIp", source_ip)
            JSON_PROPERTY("cognitoAuthenticationType", cognito_authentication_type)
            JSON_PROPERTY("cognitoAuthenticationProvider", cognito_authentication_provider)
            JSON_PROPERTY("userArn", user_arn)
            JSON_PROPERTY("userAgent", user_agent)
            JSON_PROPERTY("user", user)
          JSON_END_SERIALIZER()
      };

      class gateway_proxy_request_context {
        public:
          std::string account_id = "";
          std::string resource_id = "";
          std::string stage = "";
          std::string request_id = "";
          std::string request_time = "";
          long long request_time_epoch = 0;
          gateway_proxy_request_identity identity;
          std::string path = "";
          std::string resource_path = "";
          std::string http_method = "";
          std::string api_id = "";
          std::string protocol = "";

          JSON_BEGIN_SERIALIZER(gateway_proxy_request_context)
            JSON_PROPERTY("accountId", account_id)
            JSON_PROPERTY("resourceId", resource_id)
            JSON_PROPERTY("stage", stage)
            JSON_PROPERTY("requestId", request_id)
            JSON_PROPERTY("requestTime", request_time)
            JSON_PROPERTY("requestTimeEpoch", request_time_epoch)
            JSON_PROPERTY("identity", identity)
            JSON_PROPERTY("path", path)
            JSON_PROPERTY("resourcePath", resource_path)
            JSON_PROPERTY("httpMethod", http_method)
            JSON_PROPERTY("apiId", api_id)
            JSON_PROPERTY("protocol", protocol)
          JSON_END_SERIALIZER()
      };

      class gateway_proxy_request {
        public:
          std::string body = "";
          std::string resource = "";
          std::string path = "";
          std::string http_method = "";
          bool is_base64_encoded = false;
          std::map<std::string, std::string> query_string_parameters;
          std::map<std::string, std::vector<std::string>> multi_value_query_string_parameters;
          std::map<std::string, std::string> path_parameters;
          std::map<std::string, std::string> stage_variables;
          std::map<std::string, std::string> headers;
          std::map<std::string, std::vector<std::string>> multi_value_headers;
          gateway_proxy_request_context request_context;

          JSON_BEGIN_SERIALIZER(gateway_proxy_request)
            JSON_PROPERTY("body", body)
            JSON_PROPERTY("resource", resource)
            JSON_PROPERTY("path", path)
            JSON_PROPERTY("httpMethod", http_method)
            JSON_PROPERTY("isBase64Encoded", is_base64_encoded)
            JSON_PROPERTY("queryStringParameters", query_string_parameters)
            JSON_PROPERTY("multiValueQueryStringParameters", multi_value_query_string_parameters)
            JSON_PROPERTY("pathParameters", path_parameters)
            JSON_PROPERTY("stageVariables", stage_variables)
            JSON_PROPERTY("headers", headers)
            JSON_PROPERTY("multiValueHeaders", multi_value_headers)
            JSON_PROPERTY("requestContext", request_context)
          JSON_END_SERIALIZER()
      };
    }
  } 
}
