#include "vec.hpp"
#include <cmath>
#include <iostream>
#include <complex>
#include <type_traits>

// Implementation arithmetic:
template <typename T>
vec<T>& vec<T>::operator+=(const vec<T>& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

template <typename T>
vec<T>& vec<T>::operator-=(const vec<T>& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

template <typename T>
vec<T>& vec<T>::operator*=(T scalar){
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

template <typename T>
vec<T>& vec<T>::operator/=(T scalar){
    if(scalar != T(0)){
        x /= scalar;
    y /= scalar;
    z /= scalar;
    }else{
        throw std::invalid_argument("Devision by zero");
    }
    return *this;
}



//Implementatio Utility print function
template <typename T>
void vec<T>::print(const std::string& s) const {
    std::cout << s << "vec(" << x << ", " << y << ", " << z << ")" << std::endl;
}

template class vec<int>;
template class vec<float>;
template class vec<double>;
template class vec<std::complex<float>>;
template class vec<std::complex<double>>;

// int
template vec<int> operator+(const vec<int>&, const vec<int>&);
template vec<int> operator-(const vec<int>&, const vec<int>&);
template vec<int> operator-(const vec<int>&);
template vec<int> operator*(const vec<int>&, int);
template vec<int> operator*(int, const vec<int>&);
template vec<int> operator/(const vec<int>&, int);

// float
template vec<float> operator+(const vec<float>&, const vec<float>&);
template vec<float> operator-(const vec<float>&, const vec<float>&);
template vec<float> operator-(const vec<float>&);
template vec<float> operator*(const vec<float>&, float);
template vec<float> operator*(float, const vec<float>&);
template vec<float> operator/(const vec<float>&, float);
template bool approx(const vec<float>&, const vec<float>&, float, float);

// double
template vec<double> operator+(const vec<double>&, const vec<double>&);
template vec<double> operator-(const vec<double>&, const vec<double>&);
template vec<double> operator-(const vec<double>&);
template vec<double> operator*(const vec<double>&, double);
template vec<double> operator*(double, const vec<double>&);
template vec<double> operator/(const vec<double>&, double);
template bool approx(const vec<double>&, const vec<double>&, double, double);


// Implementation non-members
template <typename T>
vec<T> operator-(const vec<T>& v) {
    return vec(-v.x, -v.y, -v.z);
}

template <typename T>
vec<T> operator-(const vec<T>& a, const vec<T>& b) {
    return vec(a.x - b.x, a.y - b.y, a.z - b.z);
}

template <typename T>
vec<T> operator+(const vec<T>& a, const vec<T>& b) {
    return vec(a.x + b.x, a.y + b.y, a.z + b.z);
}

template <typename T>
vec<T> operator*(const vec<T>& v, T scalar) {
    return vec(v.x * scalar, v.y * scalar, v.z * scalar);
}

template <typename T>
vec<T> operator*(T scalar, const vec<T>& v) {
    return vec(v.x * scalar, v.y * scalar, v.z * scalar);
}

template <typename T>
vec<T> operator/(const vec<T>& v, T scalar) {
    if (scalar != T(0)) {
        return vec(v.x / scalar, v.y / scalar, v.z / scalar);
    } else {
        throw std::invalid_argument("Division by zero.");
    }
}

// Implementation approximate equality
template <typename T, typename>
bool approx(const vec<T>& a,
            const vec<T>& b,
            T acc,
            T eps)
{
    using real_t = decltype(std::abs(a.x));

    real_t diffX = std::abs(a.x - b.x);
    real_t diffY = std::abs(a.y - b.y);
    real_t diffZ = std::abs(a.z - b.z);

    if (diffX <= acc && diffY <= acc && diffZ <= acc)
        return true;

    real_t maxX = std::max(std::abs(a.x), std::abs(b.x));
    real_t maxY = std::max(std::abs(a.y), std::abs(b.y));
    real_t maxZ = std::max(std::abs(a.z), std::abs(b.z));

    return (diffX <= eps * maxX &&
            diffY <= eps * maxY &&
            diffZ <= eps * maxZ);
}




