#include "lasso/week2.hpp"
#include <iomanip>
#include <iostream>

int main() {
    const lasso::Matrix features{{1, 60}, {2, 65}, {3, 70}, {4, 80}, {5, 90}};
    const lasso::Vector target{52, 55, 61, 66, 70};
    const auto scaled = lasso::standardize(features);
    const auto fit = lasso::coordinate_descent(scaled.features, target, 0.10, 500);
    std::cout << std::fixed << std::setprecision(3)
              << "scaled first feature: " << scaled.features[0][0] << "\n"
              << "coefficient 1: " << fit.coefficients[0] << "\n"
              << "coefficient 2: " << fit.coefficients[1] << "\n"
              << "cost: " << fit.cost << "\n"
              << "passes: " << fit.passes << "\n";
}
