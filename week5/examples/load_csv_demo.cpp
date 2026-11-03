#include "lasso/lasso_regression.hpp"

#include <exception>
#include <iostream>

int main() {
    try {
        // Load the sample dataset from the CSV file used by the lasso demo.
        const lasso::Dataset data = lasso::load_csv("data/input/sample.csv");

        // Report the dataset dimensions so the user can confirm the data loaded correctly.
        std::cout << "Loaded " << data.features.size() << " rows and "
                  << data.features[0].size() << " features from the sample CSV.\n";
    } catch (const std::exception& error) {
        // Surface the file-loading problem to the user and exit with an error code.
        std::cerr << "Could not load the sample data: " << error.what() << "\n";
        return 1;
    }
}
