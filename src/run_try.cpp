#include <iostream>
#include <iomanip>

#include "try.hpp"

int main() {
    // Set the input value and derivative seed
    DualNumber<double> b(3.0, 1.0); // x=3.0, seed for derivative is 1.0
    //Added extra line to see how brach changes can be applied

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
