#pragma once

#include <aws/core/http/HttpResponse.h>
#include <aws/lambda-runtime/runtime.h>
#include <aws-lambda-cpp/common/json.hpp>
#include <aws-lambda-cpp/models/lambda_responses/gateway_proxy.hpp>

namespace aws_lambda_cpp {
  namespace http {
    template<typename _payloadT>
    aws::lambda_runtime::invocation_response ok(const _payloadT& payload, const std::string& content_type = "application/json") {
      aws_lambda_cpp::models::lambda_responses::gateway_proxy_response<_payloadT> res;
      res.status_code = (int)Aws::Http::HttpResponseCode::OK;
      res.set_payload(payload);
      std::string res_serialized = aws_lambda_cpp::json::serialize(res, true);
      return aws::lambda_runtime::invocation_response::success(res_serialized, content_type);
    }
  }
}

