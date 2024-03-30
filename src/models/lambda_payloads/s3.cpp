#include <aws-lambda-cpp/models/lambda_payloads/s3.hpp>

using namespace aws_lambda_cpp::models::lambda_payloads;

#define PUT_EVENT_NAME "ObjectCreated:Put"
#define DELETE_EVENT_NAME "ObjectRemoved:Delete"

bool s3_record::is_put() {
  return this->event_name == PUT_EVENT_NAME;
}

bool s3_record::is_delete() {
  return this->event_name == DELETE_EVENT_NAME;
}

