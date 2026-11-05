#include "lasso/lasso_regression.hpp"
#include <iostream>

int main() {
    std::cout << "positive: " << lasso::soft_threshold(5, 2) << "\n"
              << "negative: " << lasso::soft_threshold(-5, 2) << "\n"
              << "small value: " << lasso::soft_threshold(1, 2) << "\n";
}
