#include <string>
#include <vector>

#include "macros.h"

namespace aws_lambda_cpp {
  namespace models {
    namespace lambda_payloads {
      class s3_bucket {
        public:
          std::string name;

          JSON_BEGIN_SERIALIZER(s3_bucket)
            JSON_STRING("Name", name)
          JSON_END_SERIALIZER(s3_bucket)
      };

      class s3_object {
        public:
          std::string key;
          int size;
          std::string e_tag;
      };

      class s3 {
        s3_bucket bucket;
        s3_object object;
      };

      class record {
        public:
          std::string event_name;
          s3 s3;
      };

      class s3_request {
        public:
          std::vector<record> records;
      };

      s3_request parse_s3_request(std::string payload);
    }
  }
}
