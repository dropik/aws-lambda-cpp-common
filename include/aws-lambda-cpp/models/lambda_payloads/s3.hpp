#pragma once

#include <string>
#include <vector>
#include <map>
#include <aws/core/utils/json/JsonSerializer.h>

#include <aws-lambda-cpp/common/json.hpp>

namespace aws_lambda_cpp {
  namespace models {
    namespace lambda_payloads {
      class s3_identity {
        public:
          std::string principal_id = "";

          JSON_BEGIN_SERIALIZER(s3_identity)
            JSON_PROPERTY("principalId", principal_id)
          JSON_END_SERIALIZER()
      };

      class s3_bucket {
        public:
          std::string name = "";
          s3_identity owner_identity;
          std::string arn = "";

          JSON_BEGIN_SERIALIZER(s3_bucket)
            JSON_PROPERTY("name", name)
            JSON_PROPERTY("ownerIdentity", owner_identity)
            JSON_PROPERTY("arn", arn)
          JSON_END_SERIALIZER()
      };

      class s3_object {
        public:
          std::string key = "";
          int size = 0;
          std::string e_tag = "";
          std::string sequencer = "";

          JSON_BEGIN_SERIALIZER(s3_object)
            JSON_PROPERTY("key", key)
            JSON_PROPERTY("size", size)
            JSON_PROPERTY("eTag", e_tag)
            JSON_PROPERTY("sequencer", sequencer)
          JSON_END_SERIALIZER()
      };

      class s3_desc {
        public:
          std::string s3_schema_version = "";
          std::string configuration_id = "";
          s3_bucket bucket;
          s3_object object;

          JSON_BEGIN_SERIALIZER(s3_desc)
            JSON_PROPERTY("s3SchemaVersion", s3_schema_version)
            JSON_PROPERTY("configurationId", configuration_id)
            JSON_PROPERTY("bucket", bucket)
            JSON_PROPERTY("object", object)
          JSON_END_SERIALIZER()
      };

      class s3_request_parameters {
        public:
          std::string source_ip_address = "";

          JSON_BEGIN_SERIALIZER(s3_request_parameters)
            JSON_PROPERTY("sourceIPAddress", source_ip_address)
          JSON_END_SERIALIZER()
      };

      class s3_record {
        public:
          std::string event_version = "";
          std::string event_source = "";
          std::string aws_region = "";
          std::string event_time = "";
          std::string event_name = "";
          s3_identity user_identity;
          s3_request_parameters request_parameters;
          std::map<std::string, std::string> response_elements;
          s3_desc s3;

          bool is_put();
          bool is_delete();

          JSON_BEGIN_SERIALIZER(s3_record)
            JSON_PROPERTY("eventVersion", event_version)
            JSON_PROPERTY("eventSource", event_source)
            JSON_PROPERTY("awsRegion", aws_region)
            JSON_PROPERTY("eventTime", event_time)
            JSON_PROPERTY("eventName", event_name)
            JSON_PROPERTY("userIdentity", user_identity)
            JSON_PROPERTY("requestParameters", request_parameters)
            JSON_PROPERTY("responseElements", response_elements)
            JSON_PROPERTY("s3", s3)
          JSON_END_SERIALIZER()
      };

      class s3_request {
        public:
          std::vector<s3_record> records;

          JSON_BEGIN_SERIALIZER(s3_request)
            JSON_PROPERTY("Records", records)
          JSON_END_SERIALIZER()
      };
    }
  }
}

