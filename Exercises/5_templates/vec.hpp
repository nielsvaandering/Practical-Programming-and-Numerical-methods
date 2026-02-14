#pragma once
#include <iostream>
#include <string>
#include<complex>
#include <type_traits>

template <typename T>
class vec {
public:
    T x, y, z;

    // constructors
    vec(T x, T y, T z) : x(x), y(y), z(z) {}                   // parameterized
    vec() : vec(T(0), T(0), T(0)) {}                           // default
    vec(const vec&) = default;                                 // copy
    vec(vec&&) = default;                                      // move
    ~vec() = default;                                          // destructor

    // assignment
    vec& operator=(const vec&) = default;                      // copy assignment
    vec& operator=(vec&&) = default;                           // move assignment

    // arithmetic
    vec& operator+=(const vec& other);
    vec& operator-=(const vec& other);
    vec& operator*=(T scalar);
    vec& operator/=(T scalar);

    // utility
    void set(T a, T b, T c) { x = a; y = b; z = c; }
    void print(const std::string& s = "") const;                // for debugging

    // stream output
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const vec<U>& v);
};

// Non-member operators
template <typename T>
vec<T> operator-(const vec<T>& v);

template <typename T>
vec<T> operator-(const vec<T>& a, const vec<T>& b);

template <typename T>
vec<T> operator+(const vec<T>& a, const vec<T>& b);

template <typename T>
vec<T> operator*(const vec<T>& v, T scalar);

template <typename T>
vec<T> operator*(T scalar, const vec<T>& v);

template <typename T>
vec<T> operator/(const vec<T>& v, T scalar);

// Approximate equality
template <typename T,
          typename = std::enable_if_t<!std::is_integral_v<T>>>   // ← block int
bool approx(const vec<T>& a,
            const vec<T>& b,
            T acc = T(1e-6),
            T eps = T(1e-6));
