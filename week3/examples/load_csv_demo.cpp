#include "lasso/lasso_regression.hpp"

#include <exception>
#include <iostream>

int main() {
    try {
        const lasso::Dataset data = lasso::load_csv("data/input/sample.csv");
        std::cout << "Loaded " << data.features.size() << " rows and "
                  << data.features[0].size() << " features from the sample CSV.\n";
    } catch (const std::exception& error) {
        std::cerr << "Could not load the sample data: " << error.what() << "\n";
        return 1;
    }
}
