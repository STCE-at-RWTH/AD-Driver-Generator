#include <cmath>

// Define a custom dual number class for automatic differentiation using templates
template <typename T>
class DualNumber {
public:
    T value;   // The original value
    T tangent; // The derivative (tangent)

    explicit DualNumber(T val, T tan = T()) : value(val), tangent(tan) {}

    // Overload arithmetic operators to propagate derivatives
    DualNumber operator+(const DualNumber& other) const {
        return DualNumber(value + other.value, tangent + other.tangent);
    }

    DualNumber operator-(const DualNumber& other) const {
        return DualNumber(value - other.value, tangent - other.tangent);
    }

    DualNumber operator*(const DualNumber& other) const {
        return DualNumber(value * other.value, tangent * other.value + value * other.tangent);
    }

    DualNumber operator/(const DualNumber& other) const {
        return DualNumber(value / other.value, (tangent * other.value - value * other.tangent) / (other.value * other.value));
    }

    // Overload the multiplication operator for scalar multiplication
    DualNumber operator*(const T& scalar) const {
        return DualNumber(value * scalar, tangent * scalar);
    }

    // Overload the division operator for division by a scalar
    DualNumber operator/(const T& scalar) const {
        return DualNumber(value / scalar, tangent / scalar);
    }

    // Function to create a DualNumber from a constant value
    static DualNumber FromConstant(T val) {
        return DualNumber(val, T());
    }

    // Overload trigonometric functions for DualNumber
    DualNumber cos() const {
        return DualNumber(std::cos(value), -tangent * std::sin(value));
    }

    DualNumber sin() const {
        return DualNumber(std::sin(value), tangent * std::cos(value));
    }

    // Overload exp function for DualNumber
    DualNumber exp() const {
        return DualNumber(std::exp(value), tangent * std::exp(value));
    }

    // Overload pow function for DualNumber
    DualNumber pow(const T& exponent) const {
        return DualNumber(std::pow(value, exponent), tangent * exponent * std::pow(value, exponent - 1));
    }

};

// Define your simulation function using the template type
template <typename T>
DualNumber<T> MySimulationFunction(const DualNumber<T>& x) {
    // Example: f(x) = 27 / x
    DualNumber<T> result = DualNumber<T>::FromConstant(27) / x; // Construct DualNumber from constant value
    return result;
}

// Define your simulation function using the template type
template <typename T>
DualNumber<T> MySimulationFunction2(const DualNumber<T>& x) {
    // Example: f(x) = 27 / x * cos(x)
    // Construct DualNumber from constant value and call cos
    return (DualNumber<T>::FromConstant(27) / x) * x.cos();
}

