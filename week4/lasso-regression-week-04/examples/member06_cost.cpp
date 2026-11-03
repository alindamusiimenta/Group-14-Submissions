#include "lasso/lasso_regression.hpp"
#include <iostream>

int main() {
    const lasso::Matrix x{{1, 2}, {2, 1}};
    const lasso::Vector y{5, 4};
    std::cout << "LASSO cost: " << lasso::lasso_cost(x, y, {1, 2}, 0.5) << "\n";
}
