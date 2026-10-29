#include "lasso/lasso_regression.hpp"
#include <iostream>

int main() {
    const auto baseline = lasso::linear_regression_baseline({1, 2, 3, 4, 5}, {52, 55, 61, 66, 70});
    std::cout << "baseline intercept: " << baseline.intercept << "\n"
              << "baseline slope: " << baseline.slope << "\n"
              << "baseline MSE: " << baseline.mse << "\n";
}
