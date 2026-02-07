#include "vec.hpp"
#include<cmath>
#include<iostream>

// Implementation arithmetic:

vec& vec::operator+=(const vec& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

vec& vec::operator-=(const vec& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

vec& vec::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}


vec& vec::operator/=(double scalar) {
    if(scalar != 0){x /= scalar;
    y /= scalar;
    z /= scalar;
}else {
        throw std::invalid_argument("Division by zero.");
    }
    return *this;
}

//Implementatio Utility print function

void vec::print(const std::string& s) const {
    std::cout << s << "vec(" << x << ", " << y << ", " << z << ")" << std::endl;
}

// Implementation non-members
vec operator-(const vec& v) {
    return vec(-v.x, -v.y, -v.z);
}

vec operator-(const vec& a, const vec& b) {
    return vec(a.x - b.x, a.y - b.y, a.z - b.z);
}

vec operator+(const vec& a, const vec& b) {
    return vec(a.x + b.x, a.y + b.y, a.z + b.z);
}

vec operator*(const vec& v, double scalar) {
    return vec(v.x * scalar, v.y * scalar, v.z * scalar);
}

vec operator*(double scalar, const vec& v) {
    return vec(v.x * scalar, v.y * scalar, v.z * scalar);
}

vec operator/(const vec& v, double scalar) {
    if (scalar != 0) {
        return vec(v.x / scalar, v.y / scalar, v.z / scalar);
    } else {
        throw std::invalid_argument("Division by zero.");
    }
}

// Implementation approximate equality
bool approx(const vec& a, const vec& b, double acc = 1e-6, double eps = 1e-6) {
    double diffX = std::abs(a.x - b.x);
    double diffY = std::abs(a.y - b.y);
    double diffZ = std::abs(a.z - b.z);

    if (diffX <= acc && diffY <= acc && diffZ <= acc) return true;  // absolute tolerance

    double maxX = std::max(std::abs(a.x), std::abs(b.x));
    double maxY = std::max(std::abs(a.y), std::abs(b.y));
    double maxZ = std::max(std::abs(a.z), std::abs(b.z));

    return (diffX <= eps * maxX && diffY <= eps * maxY && diffZ <= eps * maxZ);   // relative tolerance
}



