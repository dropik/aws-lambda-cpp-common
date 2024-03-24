#pragma once

#include <string>
#include <vector>
#include <aws/core/utils/json/JsonSerializer.h>

#include "aws-lambda-cpp/common/json.hpp"

namespace aws_lambda_cpp {
  namespace models {
    namespace lambda_payloads {
      class s3_bucket {
        public:
          std::string name = "";

          JSON_BEGIN_SERIALIZER(s3_bucket)
            JSON_PROPERTY("name", name)
          JSON_END_SERIALIZER()
      };

      class s3_object {
        public:
          std::string key = "";
          int size = 0;
          std::string e_tag = "";

          JSON_BEGIN_SERIALIZER(s3_object)
            JSON_PROPERTY("key", key)
            JSON_PROPERTY("size", size)
            JSON_PROPERTY("eTag", e_tag)
          JSON_END_SERIALIZER()
      };

      class s3_desc {
        public:
          s3_bucket bucket;
          s3_object object;

          JSON_BEGIN_SERIALIZER(s3_desc)
            JSON_PROPERTY("bucket", bucket)
            JSON_PROPERTY("object", object)
          JSON_END_SERIALIZER()
      };

      class record {
        public:
          std::string event_name = "";
          s3_desc s3;

          JSON_BEGIN_SERIALIZER(record)
            JSON_PROPERTY("eventName", event_name)
            JSON_PROPERTY("s3", s3)
          JSON_END_SERIALIZER()
      };

      class s3_request {
        public:
          std::vector<record> records;

          JSON_BEGIN_SERIALIZER(s3_request)
            JSON_PROPERTY("Records", records)
          JSON_END_SERIALIZER()
      };
    }
  }
}

