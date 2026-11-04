// Demonstrates fitting methods, prediction, and train/test splitting.
#include "linreg/linear_regression.hpp"
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    // Input feature: hours studied. Target: the corresponding examination scores.
    const std::vector<double> hours{1, 2, 3, 4, 5};
    const std::vector<double> scores{52, 55, 61, 66, 70};
    linreg::LinearRegression model;

    // 1. Fit the model using the direct closed-form least-squares method.
    const auto result = model.fit_closed_form(hours, scores);
    std::cout << std::fixed << std::setprecision(3)
              << "score = " << result.intercept << " + " << result.slope << " * hours\n"
              << "R^2 = " << result.r_squared << "\n"
              << "Prediction for 6 hours = " << model.predict(6) << "\n";

    // 2. Fit again using batch gradient descent for comparison.
    const auto gd = model.fit_gradient_descent(hours, scores, 0.01, 5000);
    std::cout << "Gradient-descent slope = " << gd.slope << "\n";

    // 3. Reserve observations for testing rather than using all data for training.
    const auto split = linreg::train_test_split(hours, scores, 0.2, 42, true);
    // 4. Train with stochastic gradient descent using only the training subset.
    model.fit_stochastic_gradient_descent(split.train_x, split.train_y, 0.001, 2000, 42);
    // Show the subset sizes and predict the first held-out input value.
    std::cout << "Training observations = " << split.train_x.size()
              << ", testing observations = " << split.test_x.size() << "\n"
              << "Test prediction for first held-out value = "
              << model.predict(split.test_x.front()) << "\n";
}
