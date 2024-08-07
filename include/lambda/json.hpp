#pragma once

#include <map>
#include <string>
#include <vector>
#include <type_traits>

#include <aws/core/utils/json/JsonSerializer.h>

#include "nullable.hpp"

namespace lambda {
namespace json {

extern Aws::Utils::Json::JsonValue null_json;

template<typename T>
class json_serializer {
 protected:
  using target = T;
  typedef Aws::Utils::Json::JsonValue json_value;
  typedef Aws::Utils::Json::JsonView json_view;
  typedef std::function<void(target &, const json_view &)> deserializer;
  typedef std::function<void(const target &, json_value &)> serializer;

  std::map<std::string, deserializer> deserializers;
  std::map<std::string, serializer> serializers;

  void deserialize_simple(std::string &s, const json_view &v) {
    s = v.AsString();
  }

  void serialize_simple(const std::string &s, json_value &v) {
    v.AsString(s);
  }

  void deserialize_simple(int &i, const json_view &v) {
    i = v.AsInteger();
  }

  void serialize_simple(const int &i, json_value &v) {
    v.AsInteger(i);
  }

  void deserialize_simple(long long &l, const json_view &v) {
    l = v.AsInt64();
  }

  void serialize_simple(const long long &l, json_value &v) {
    v.AsInt64(l);
  }

  void deserialize_simple(bool &b, const json_view &v) {
    b = v.AsBool();
  }

  void serialize_simple(const bool &b, json_value &v) {
    v.AsBool(b);
  }

  void deserialize_simple(double &d, const json_view &v) {
    d = v.AsDouble();
  }

  void serialize_simple(const double &d, json_value &v) {
    v.AsDouble(d);
  }

  void deserialize_simple(long double &d, const json_view &v) {
    d = v.AsDouble();
  }

  void serialize_simple(const long double &d, json_value &v) {
    v.AsDouble((double)d);
  }

  template<typename t_next>
  void deserialize_simple(t_next &t, const json_view &v) {
    typename t_next::json_serializer s;
    s.deserialize(t, v);
  }

  template<typename t_next>
  void serialize_simple(const t_next &t, json_value &v) {
    typename t_next::json_serializer s;
    s.serialize(t, v);
  }

  template<typename t_item>
  void deserialize_simple(std::vector<t_item> &arr, const json_view &v) {
    auto json_array = v.AsArray();
    auto length = json_array.GetLength();
    for (int i = 0; i < length; i++) {
      json_view item_view = json_array.GetItem(i);
      t_item item;
      deserialize_simple(item, item_view);
      arr.push_back(item);
    }
  }

  template<typename t_item>
  void serialize_simple(const std::vector<t_item> &arr, json_value &v) {
    std::vector<json_value> json_array;
    for (int i = 0; i < arr.size(); i++) {
      json_value json_item;
      t_item item = arr[i];
      serialize_simple(item, json_item);
      json_array.push_back(json_item);
    }
    Aws::Utils::Array<json_value> array_to_insert(json_array.data(), json_array.size());
    v.AsArray(array_to_insert);
  }

  template<typename t_item>
  void deserialize_simple(std::map<std::string, t_item> &d, const json_view &v) {
    auto json_map = v.GetAllObjects();
    for (const auto &json_property : json_map) {
      t_item item;
      deserialize_simple(item, json_property.second);
      d[json_property.first] = item;
    }
  }

  template<typename t_item>
  void serialize_simple(const std::map<std::string, t_item> &d, json_value &v) {
    for (const auto &item : d) {
      json_value next;
      serialize_simple(item.second, next);
      v.WithObject(item.first, next);
    }
  }

  template<typename t_nullable>
  void deserialize_simple(lambda::nullable<t_nullable> &n, const json_view &v) {
    if (v.IsNull()) {
      n.clear();
    } else {
      t_nullable value;
      deserialize_simple(value, v);
      n = value;
    }
  }

  template<typename t_nullable>
  void serialize_simple(const lambda::nullable<t_nullable> &n, json_value &v) {
    if (!n.has_value()) {
      json_value null(lambda::json::null_json);
      v.AsObject(null);
    } else {
      t_nullable value = n.get_value();
      serialize_simple(value, v);
    }
  }

 public:
  void deserialize(T &result, const json_view &v) {
    for (const auto &d : deserializers) {
      if (v.KeyExists(d.first)) {
        d.second(result, v.GetObject(d.first));
      }
    }
  }

  void serialize(const T &model, json_value &v) {
    for (const auto &s : serializers) {
      json_value next;
      s.second(model, next);
      v.WithObject(s.first, next);
    }
  }
};

template<typename T, class Enabled = void>
struct serializer;

template<typename T>
struct serializer<T, typename std::enable_if<std::is_class<typename T::json_serializer>::value>::type> {
  static std::string serialize(const T &model, bool compact = false) {
    Aws::Utils::Json::JsonValue value;
    typename T::json_serializer s;
    s.serialize(model, value);
    Aws::Utils::Json::JsonView view = value.View();
    if (compact) {
      return view.WriteCompact();
    } else {
      return view.WriteReadable();
    }
  }

  static T deserialize(const std::string &json) {
    T result;
    Aws::Utils::Json::JsonValue value(json);
    assert(value.WasParseSuccessful());
    Aws::Utils::Json::JsonView view = value.View();
    typename T::json_serializer s;
    s.deserialize(result, view);
    return result;
  }
};

template<typename TItem>
struct serializer<std::vector<TItem>, typename std::enable_if<std::is_class<typename TItem::json_serializer>::value>::type> {
  static std::string serialize(const std::vector<TItem> &model, bool compact = false) {
    Aws::Utils::Json::JsonValue value;
    typename TItem::json_serializer s;

    std::vector<Aws::Utils::Json::JsonValue> json_array;
    for (int i = 0; i < model.size(); i++) {
      Aws::Utils::Json::JsonValue json_item;
      TItem item = model[i];
      s.serialize(item, json_item);
      json_array.push_back(json_item);
    }
    Aws::Utils::Array<Aws::Utils::Json::JsonValue> array_to_insert(json_array.data(), json_array.size());
    value.AsArray(array_to_insert);

    Aws::Utils::Json::JsonView view = value.View();
    if (compact) {
      return view.WriteCompact();
    } else {
      return view.WriteReadable();
    }
  }

  static std::vector<TItem> deserialize(const std::string &json) {
    std::vector<TItem> result;
    Aws::Utils::Json::JsonValue value(json);
    assert(value.WasParseSuccessful());
    Aws::Utils::Json::JsonView view = value.View();
    typename TItem::json_serializer s;

    auto json_array = view.AsArray();
    auto length = json_array.GetLength();
    for (int i = 0; i < length; i++) {
      Aws::Utils::Json::JsonView item_view = json_array.GetItem(i);
      TItem item;
      s.deserialize(item, item_view);
      result.push_back(item);
    }

    return result;
  }
};

template<typename T>
std::string serialize(const T &model, bool compact = false) {
  return serializer<T>::serialize(model, compact);
}

template<typename T>
T deserialize(const std::string &json) {
  return serializer<T>::deserialize(json);
}

}
}

#define JSON_BEGIN_SERIALIZER(name)                                             \
  class json_serializer : public lambda::json::json_serializer<name> {          \
    using target = name;                                                        \
    public:                                                                     \
      json_serializer() {

#define JSON_END_SERIALIZER() \
      }                       \
  };

#define JSON_PROPERTY(key, field)                                   \
  this->deserializers[key] = [&](target& t, const Aws::Utils::Json::JsonView& v) {   \
    json_serializer::deserialize_simple(t.field, v);                                 \
  };                                                                \
  this->serializers[key] = [&](const target& t, Aws::Utils::Json::JsonValue& v) {    \
    json_serializer::serialize_simple(t.field, v);                                   \
  };
