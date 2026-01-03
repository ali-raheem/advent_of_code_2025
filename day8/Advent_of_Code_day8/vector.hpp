#pragma once

#include <array>
#include <cmath>
#include <numeric>

template <typename T, size_t N>
class Vector {

private:
  std::array<T, N> v;

public:
  Vector() : v{} {}
  
  template<typename... Args>
  Vector(Args... args) : v{static_cast<T>(args)...} {}

  Vector(const std::array<T, N>& arr) : v(arr) {}

  // operator overloads
  T& operator[](size_t i){return v[i];}

  // vector ones
  Vector operator+(const Vector& that) const {
    Vector res;
    for(int i = 0; i < N; i++) {
      res[i] = v[i] + that.v[i];
    }
    return res;
  }
  Vector operator-(const Vector& that) const {
    Vector res;
    for(int i = 0; i < N; i++) {
      res[i] = v[i] - that.v[i];
    }
    return res;
  }
  Vector& operator+=(const Vector& that) const {
    for(int i = 0; i < N; i++) {
      v[i] += that.v[i];
    }
    return *this;
  }
  Vector& operator-=(const Vector& that) const {
    for(int i = 0; i < N; i++) {
      v[i] -= that.v[i];
    }
    return *this;
  }
  // scalrs
  Vector operator*(T scalar) const {
    Vector res;
    for(int i = 0; i < N; i++) {
      res[i] = v[i] * scalar;
    }
    return res;
  }
  Vector operator/(T scalar) const {
    Vector res;
    for(int i = 0; i < N; i++) {
      res[i] = v[i] / scalar;
    }
    return res;
  }
  //comps
  bool operator==(const Vector& that) const {
    return v == that.v;
  }
  bool operator!=(const Vector& that) const {
    return v != that.v;
  }
  //distance
  T dsq(const Vector& that) const {
    T res = 0;
    for(int i = 0; i < N; i++) {
      res += (v[i] - that.v[i]) * (v[i] - that.v[i]);
    }
    return res;
  }
};

//ffs
template <typename T, size_t N>
Vector<T, N> operator*(T scalar, const Vector<T, N>& v) {
  return v * scalar;
}