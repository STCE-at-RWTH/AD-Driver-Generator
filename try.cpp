#include <iostream>
#include <iomanip>
#include <cmath>

// Define a custom dual number class for automatic differentiation using templates
template <typename T>
class DualNumber {
public:
    T value;   // The original value
    T tangent; // The derivative (tangent)

    DualNumber(T val, T tan = T()) : value(val), tangent(tan) {}

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

int main() {
    // Set the input value and derivative seed
    DualNumber<double> b(3.0, 1.0); // x=3.0, seed for derivative is 1.0

    // Call the simulation function
    DualNumber<double> result = MySimulationFunction2(b);

    // The 'result' now holds the value and its derivative
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "f (b) = " << result.value << std::endl;       // Original value
    std::cout << "f'(b) = " << result.tangent << std::endl;   // Derivative (tangent)

        // Set the input value and derivative seed
    double pi = 3.141592653589793;
    DualNumber<double> x(pi, 1.0); // x=pi, seed for derivative is 1.0

    // Call the trigonometric functions and print the results
    DualNumber<double> cos_result = x.cos();
    DualNumber<double> sin_result = x.sin();
    DualNumber<double> exp_result = x.exp();
    DualNumber<double> pow_result = x.pow(2.0);
    std::cout << "-----------------------------------------" << std::endl;
    // Set the width for value and tangent output
    int width = 15;
    // Print the results with aligned columns
    std::cout << std::left << std::setw(width) << "Function" << std::left << std::setw(width) << "Value" << std::left << std::setw(width) << "Derivative" << std::endl;
    std::cout << std::left << std::setw(width) << "cos(x)"   << std::left << std::setw(width) << cos_result.value     << std::left << std::setw(width)    << cos_result.tangent << std::endl;
    std::cout << std::left << std::setw(width) << "sin(x)"   << std::left << std::setw(width) << sin_result.value     << std::left << std::setw(width)    << sin_result.tangent << std::endl;
    std::cout << std::left << std::setw(width) << "exp(x)"   << std::left << std::setw(width) << exp_result.value     << std::left << std::setw(width)    << exp_result.tangent << std::endl;
    std::cout << std::left << std::setw(width) << "pow(x,2)" << std::left << std::setw(width) << pow_result.value     << std::left << std::setw(width)    << pow_result.tangent << std::endl;

    return 0;
}