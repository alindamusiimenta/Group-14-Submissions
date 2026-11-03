#include "linreg/linear_regression.hpp"

#include <iostream>
#include <vector>

int main() {
    const std::vector<double> study_hours{1, 2, 3, 4, 5};
    const std::vector<double> scores{52, 55, 61, 66, 70};

    linreg::LinearRegression baseline;
    const linreg::FitResult result = baseline.fit_closed_form(study_hours, scores);

    std::cout << "One-feature linear regression baseline\n"
              << "Intercept: " << result.intercept << "\n"
              << "Slope: " << result.slope << "\n"
              << "Training MSE: " << result.mse << "\n";
}
