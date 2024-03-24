#pragma once

#include <map>
#include <string>
#include <vector>

#include <aws/core/utils/json/JsonSerializer.h>

namespace aws_lambda_cpp {
  namespace json {
    template<typename T>
    class json_serializer {
      protected:
        typedef T target;
        typedef Aws::Utils::Json::JsonValue json_value;
        typedef Aws::Utils::Json::JsonView json_view;
        typedef std::function<void(target&, const json_view&)> deserializer;
        typedef std::function<void(const target&, json_value&)> serializer;

        std::map<std::string, deserializer> deserializers;
        std::map<std::string, serializer> serializers;

        void deserialize(std::string& s, const json_view& v) {
          s = v.AsString();
        }

        void serialize(const std::string& s, json_value& v) {
          v.AsString(s);
        }

        void deserialize(int& i, const json_view& v) {
          i = v.AsInteger();
        }

        void serialize(const int& i, json_value& v) {
          v.AsInteger(i);
        }

        void deserialize(long long& l, const json_view& v) {
          l = v.AsInt64();
        }

        void serialize(const long long& l, json_value& v) {
          v.AsInt64(l);
        }

        void deserialize(bool& b, const json_view& v) {
          b = v.AsBool();
        }

        void serialize(const bool& b, json_value& v) {
          v.AsBool(b);
        }

        void deserialize(double& d, const json_view& v) {
          d = v.AsDouble();
        }

        void serialize(const double& d, json_value& v) {
          v.AsDouble(d);
        }

        template<typename t_next>
        void deserialize(t_next& t, const json_view& v) {
          typename t_next::json_serializer s;
          s.deserialize(t, v);
        }

        template<typename t_next>
        void serialize(const t_next& t, json_value& v) {
          typename t_next::json_serializer s;
          s.serialize(t, v);
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

        template<typename t_item>
        void serialize(const std::vector<t_item>& arr, json_value& v) {
          std::vector<json_value> json_array;
          for (int i = 0; i < arr.size(); i++) {
            json_value json_item;
            t_item item = arr[i];
            serialize(item, json_item);
            json_array.push_back(json_item);
          }
          Aws::Utils::Array<json_value> array_to_insert(json_array.data(), json_array.size());
          v.AsArray(array_to_insert);
        }

        template<typename t_item>
        void deserialize(std::map<std::string, t_item>& d, const json_view& v) {
          auto json_map = v.GetAllObjects();
          for (const auto& json_property : json_map) {
            t_item item;
            deserialize(item, json_property.second);
            d[json_property.first] = item;
          }
        }

        template<typename t_item>
        void serialize(const std::map<std::string, t_item>& d, json_value& v) {
          for (const auto& item : d) {
            json_value next;
            serialize(item.second, next);
            v.WithObject(item.first, next);
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
        
        void serialize(const T& model, json_value& v) {
          for (const auto& s : serializers) {
            json_value next;
            s.second(model, next);
            v.WithObject(s.first, next);
          }
        }
    };

    
    template<typename T>
    T deserialize(const std::string& json) {
      T result;
      Aws::Utils::Json::JsonValue value(json);
      assert(value.WasParseSuccessful());
      Aws::Utils::Json::JsonView view = value.View();
      typename T::json_serializer s;
      s.deserialize(result, view);
      return result;
    }

    template<typename T>
    std::string serialize(const T& model) {
      Aws::Utils::Json::JsonValue value;
      typename T::json_serializer s;
      s.serialize(model, value);
      std::string result = value.View().WriteReadable();
      return result;
    }
  }
}

#define JSON_BEGIN_SERIALIZER(name)                                         \
  class json_serializer : public aws_lambda_cpp::json::json_serializer<name> {   \
    public:                                                                 \
      json_serializer() {

#define JSON_END_SERIALIZER() \
      }                       \
  };

#define JSON_PROPERTY(key, field)                                   \
  this->deserializers[key] = [&](target& t, const json_view& v) {   \
    deserialize(t.field, v);                                        \
  };                                                                \
  this->serializers[key] = [&](const target& t, json_value& v) {    \
    serialize(t.field, v);                                          \
  };

