// Member 05 demonstration: one-feature regression using study hours and scores.
#include "linreg/linear_regression.hpp"

#include <iostream>
#include <vector>

int main() {
    // Each study-hours value is paired with the examination score at the same index.
    const std::vector<double> study_hours{1, 2, 3, 4, 5};
    const std::vector<double> scores{52, 55, 61, 66, 70};

    // Create the model object that will learn the best-fit straight line.
    linreg::LinearRegression baseline;
    // Train with the direct least-squares method and collect the fitted results.
    const linreg::FitResult result = baseline.fit_closed_form(study_hours, scores);

    // Display the learned intercept, slope, and training error.
    std::cout << "One-feature linear regression baseline\n"
              << "Intercept: " << result.intercept << "\n"
              << "Slope: " << result.slope << "\n"
              << "Training MSE: " << result.mse << "\n";
}
