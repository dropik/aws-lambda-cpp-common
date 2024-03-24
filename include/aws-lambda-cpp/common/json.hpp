#pragma once

#include <map>
#include <string>
#include <vector>

#include <aws/core/utils/json/JsonSerializer.h>

namespace aws_lambda_cpp {
  namespace json {
    template<typename T>
    class serializer {
      protected:
        typedef T target;
        typedef Aws::Utils::Json::JsonView json_view;
        typedef std::function<void(target&, const json_view&)> deserializer;
        std::map<std::string, deserializer> deserializers;

        void deserialize(std::string& s, const json_view& v) {
          s = v.AsString();
        }

        void deserialize(int& i, const json_view& v) {
          i = v.AsInteger();
        }

        void deserialize(bool& b, const json_view& v) {
          b = v.AsBool();
        }

        void deserialize(double& d, const json_view& v) {
          d = v.AsDouble();
        }

        template<typename t_next>
        void deserialize(t_next& t, const json_view& v) {
          typename t_next::serializer s;
          s.deserialize(t, v);
        }

        template<typename t_item>
        void deserialize(std::vector<t_item>& arr, const json_view& v) {
          auto json_array = v.AsArray();
          int length = json_array.GetLength();
          for (int i = 0; i < length; i++) {
            json_view item_view = json_array.GetItem(i);
            t_item item;
            deserialize(item, item_view);
            arr.push_back(item);
          }
        }

      public:
        void deserialize(T& result, const json_view& v) {
          for (const auto& d : deserializers) {
            if (v.KeyExists(d.first)) {
              d.second(result, v.GetObject(d.first));
            }
          }
        }
    };

    
    template<typename T>
    T deserialize(const std::string& json) {
      T result;
      Aws::Utils::Json::JsonValue value(json);
      assert(value.WasParseSuccessful());
      Aws::Utils::Json::JsonView view = value.View();
      typename T::serializer s;
      s.deserialize(result, view);
      return result;
    }
  }
}

#define JSON_BEGIN_SERIALIZER(name)                                   \
  class serializer : public aws_lambda_cpp::json::serializer<name> {  \
    public:                                                           \
      serializer() {

#define JSON_END_SERIALIZER() \
      }                       \
  };

#define JSON_PROPERTY(key, field)                                   \
  this->deserializers[key] = [&](target& t, const json_view& v) {   \
    deserialize(t.field, v);                                        \
  };

