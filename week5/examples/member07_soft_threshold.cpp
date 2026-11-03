#include "lasso/week3.hpp"
#include <iostream>

int main() {
    std::cout << "positive: " << lasso::soft_threshold(5, 2) << "\n"
              << "negative: " << lasso::soft_threshold(-5, 2) << "\n"
              << "small value: " << lasso::soft_threshold(1, 2) << "\n";
    const auto selected = lasso::selected_features({2.4, 0.0000001, -1.1});
    std::cout << "selected feature indexes: ";
    for (std::size_t index : selected) std::cout << index << ' ';
    std::cout << '\n';
}
