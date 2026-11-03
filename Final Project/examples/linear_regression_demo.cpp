#include "linreg/linear_regression.hpp"
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    const std::vector<double> hours{1, 2, 3, 4, 5};
    const std::vector<double> scores{52, 55, 61, 66, 70};
    linreg::LinearRegression model;

    const auto result = model.fit_closed_form(hours, scores);
    std::cout << std::fixed << std::setprecision(3)
              << "score = " << result.intercept << " + " << result.slope << " * hours\n"
              << "R^2 = " << result.r_squared << "\n"
              << "Prediction for 6 hours = " << model.predict(6) << "\n";

    const auto gd = model.fit_gradient_descent(hours, scores, 0.01, 5000);
    std::cout << "Gradient-descent slope = " << gd.slope << "\n";

    const auto split = linreg::train_test_split(hours, scores, 0.2, 42, true);
    model.fit_stochastic_gradient_descent(split.train_x, split.train_y, 0.001, 2000, 42);
    std::cout << "Training observations = " << split.train_x.size()
              << ", testing observations = " << split.test_x.size() << "\n"
              << "Test prediction for first held-out value = "
              << model.predict(split.test_x.front()) << "\n";
}
