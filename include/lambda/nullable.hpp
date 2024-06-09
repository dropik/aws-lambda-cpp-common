#pragma once

#include <cassert>

namespace lambda {

template<typename T>
class nullable {
 private:
  T m_value;
  bool m_has_value = false;

  template<typename V>
  void set(const V &v) {
    m_value = v;
    m_has_value = true;
  }

  void set(const nullable<T> &t) {
    if (t.has_value()) {
      m_value = t.get_value();
      m_has_value = true;
    } else {
      m_has_value = false;
    }
  }

 public:
  T get_value() const {
    assert(m_has_value);
    return m_value;
  }

  bool has_value() const {
    return m_has_value;
  }

  void clear() {
    m_has_value = false;
  }

  nullable() {}
  virtual ~nullable() {}

  template<typename V>
  nullable(const V &v) {
    set(v);
  }

  nullable(const nullable<T> &t) {
    set(t);
  }

  template<typename V>
  nullable<T> &operator=(const V &v) {
    set(v);
    return *this;
  }

  nullable<T> &operator=(const nullable<T> &t) {
    set(t);
    return *this;
  }
};

}
