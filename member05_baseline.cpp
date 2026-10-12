
#include "lasso/lasso_regression.hpp" // Includes the linear regression functions
#include <iostream> // Allows us to display output on the screen

int main() {
    // Calculate the linear regression baseline using input data.
    // X values: 1, 2, 3, 4
    // Y values: 3, 5, 7, 9
    const auto result = lasso::linear_regression_baseline(
        {1, 2, 3, 4}, {3, 5, 7, 9}
    );

    // Display the intercept (where the line crosses the Y-axis).
    std::cout << "baseline intercept: " << result.intercept << "\n"

              // Display the slope (how much Y changes when X increases by 1).
              << "baseline slope: " << result.slope << "\n";
}
