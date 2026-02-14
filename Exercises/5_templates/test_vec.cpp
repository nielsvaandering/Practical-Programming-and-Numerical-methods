#include <iostream>
#include <cassert>
#include <complex>
#include <type_traits>    // <-- needed for if constexpr
#include "vec.hpp"

// Template function to test basic operations for a given type
template <typename T>
void test_vec_operations() {
    std::cout << "Testing vec<" << typeid(T).name() << ">" << std::endl;

    // Test constructors
    vec<T> default_vec;
    assert(default_vec.x == T(0) && default_vec.y == T(0) && default_vec.z == T(0));

    vec<T> param_vec(T(1), T(2), T(3));
    assert(param_vec.x == T(1) && param_vec.y == T(2) && param_vec.z == T(3));

    // Test copy constructor
    vec<T> copy_vec(param_vec);
    assert(copy_vec.x == T(1) && copy_vec.y == T(2) && copy_vec.z == T(3));

    // Test set method
    default_vec.set(T(4), T(5), T(6));
    assert(default_vec.x == T(4) && default_vec.y == T(5) && default_vec.z == T(6));

    // Test addition
    vec<T> add_vec(T(1), T(2), T(3));
    add_vec += param_vec;
    assert(add_vec.x == T(2) && add_vec.y == T(4) && add_vec.z == T(6));

    // Test subtraction
    vec<T> sub_vec(T(5), T(6), T(7));
    sub_vec -= param_vec;
    assert(sub_vec.x == T(4) && sub_vec.y == T(4) && sub_vec.z == T(4));

    // Test multiplication
    vec<T> mul_vec(T(2), T(3), T(4));
    mul_vec *= T(2);
    assert(mul_vec.x == T(4) && mul_vec.y == T(6) && mul_vec.z == T(8));

    // Test division
    vec<T> div_vec(T(6), T(8), T(10));
    div_vec /= T(2);
    assert(div_vec.x == T(3) && div_vec.y == T(4) && div_vec.z == T(5));

    // Test non-member operators
    vec<T> a(T(1), T(2), T(3));
    vec<T> b(T(4), T(5), T(6));
    
    // Addition
    vec<T> sum = a + b;
    assert(sum.x == T(5) && sum.y == T(7) && sum.z == T(9));

    // Subtraction
    vec<T> diff = a - b;
    assert(diff.x == T(-3) && diff.y == T(-3) && diff.z == T(-3));

    // Negation
    vec<T> neg = -a;
    assert(neg.x == T(-1) && neg.y == T(-2) && neg.z == T(-3));

    // Scalar multiplication
    vec<T> scaled = a * T(2);
    assert(scaled.x == T(2) && scaled.y == T(4) && scaled.z == T(6));

    // Test approximate equality (skip for integral types)
    if constexpr (!std::is_integral_v<T>) {
        vec<T> close1(T(1.0), T(2.0), T(3.0));
        vec<T> close2(T(1.0000001), T(1.9999999), T(3.0000001));
        assert(approx(close1, close2));
    }

    // Division by zero test
    try {
        vec<T> zero_div_vec(T(6), T(8), T(10));
        zero_div_vec /= T(0);
        assert(false && "Division by zero should throw an exception");
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught expected division by zero exception" << std::endl;
    }

    std::cout << "All tests passed for vec<" << typeid(T).name() << ">" << std::endl;
}

// Test complex types separately
template <typename T>
void test_complex_vec() {
    std::cout << "Testing vec<std::complex<" << typeid(T).name() << ">>" << std::endl;

    using Complex = std::complex<T>;
    
    vec<Complex> default_vec;
    assert(default_vec.x == Complex(0) && 
           default_vec.y == Complex(0) && 
           default_vec.z == Complex(0));

    vec<Complex> param_vec(
        Complex(1, 2), 
        Complex(3, 4), 
        Complex(5, 6)
    );

    // Basic operations (like multiplication)
    param_vec *= Complex(2, 0);

    std::cout << "Complex vec tests completed" << std::endl;
}

int main() {
    std::cout <<"This testfile is written by ai, so I hope it tests all cases \n";
    // Test numeric types
    test_vec_operations<int>();
    test_vec_operations<float>();
    test_vec_operations<double>();
    
    // Test complex types
    test_complex_vec<float>();
    test_complex_vec<double>();

    std::cout << "All vec template tests completed successfully!" << std::endl;
    return 0;
}
