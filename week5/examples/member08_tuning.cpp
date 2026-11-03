#include "lasso/week3.hpp"
#include <iostream>

int main() {
    const lasso::Matrix features{{-1.4, -1.2}, {-0.7, -0.7}, {0.0, -0.3}, {0.7, 0.6}, {1.4, 1.6}};
    const lasso::Vector target{52, 55, 61, 66, 70};
    const double best = lasso::choose_lambda(features, target, {0.01, 0.10, 0.50});
    std::cout << "chosen lambda: " << best << "\n";
}
