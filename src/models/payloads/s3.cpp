#include <lambda/models/payloads/s3.hpp>

#define PUT_EVENT_NAME "ObjectCreated:Put"
#define DELETE_EVENT_NAME "ObjectRemoved:Delete"

namespace lambda {
namespace models {
namespace payloads {

bool s3_record::is_put() const {
  return this->event_name == PUT_EVENT_NAME;
}

bool s3_record::is_delete() const {
  return this->event_name == DELETE_EVENT_NAME;
}

}
}
}
