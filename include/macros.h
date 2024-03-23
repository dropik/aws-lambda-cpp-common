#pragma once

#include <aws/core/utils/json/JsonSerializer.h>
#include <map>

#define STR(s) #s
#define XSTR(s) STR(s)

namespace aws_lambda_cpp {
  class json_serialization_unit {
    public:
      json_serialization_unit(std::function<void(const Aws::Utils::Json::JsonView& json_view)> deserializer) {
        this->deserializer = deserializer;
      }

      std::function<void(const Aws::Utils::Json::JsonView&)> deserializer;
  };
}

#define JSON_BEGIN_SERIALIZER(name)                         \
  name deserialize(Aws::Utils::Json::JsonView json_view) {  \
    std::map<std::string, json_serialization_unit> units;   \
    name result;

#define JSON_END_SERIALIZER(name)           \
    for (const auto& u : units) {           \
      if (json_view.KeyExists(u.first)) {   \
        u.second.deserializer(json_view);   \
      }                                     \
    }                                       \
    return result;                          \
  }     

#define JSON_STRING(key, field)                                           \
    units[key] =                                                          \
      json_serialization_unit([&](const Aws::Utils::Json::JsonView& v) {  \
        result.field = v.GetString(key);                                  \
      });
