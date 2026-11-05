// Member 05: Linear Regression demonstration.
// Demonstrates different methods of training and prediction.

#include "linreg/linear_regression.hpp"
#include <iomanip>
#include <iostream>
#include <vector>

int main() {

    // Store study hours (inputs) and examination scores (outputs).
    const std::vector<double> hours{1, 2, 3, 4, 5};
    const std::vector<double> scores{52, 55, 61, 66, 70};

    // Create an instance of the LinearRegression class.
    linreg::LinearRegression model;

    // Fit the best regression line using the least squares method.
    const auto result = model.fit_closed_form(hours, scores);

    // Display the regression equation, R-squared and predicted score.
    std::cout << std::fixed << std::setprecision(3)
              << "score = " << result.intercept
              << " + " << result.slope << " * hours\n"
              << "R^2 = " << result.r_squared << "\n"
              << "Prediction for 6 hours = "
              << model.predict(6) << "\n";

    // Train the model using batch gradient descent.
    // Uses a learning rate of 0.01 for 5000 iterations.
    const auto gd =
        model.fit_gradient_descent(hours, scores, 0.01, 5000);

    // Display the slope obtained from gradient descent.
    std::cout << "Gradient-descent slope = "
              << gd.slope << "\n";

    // Split the data: 80% for training and 20% for testing.
    // Seed 42 ensures reproducible shuffling.
    const auto split =
        linreg::train_test_split(hours, scores, 0.2, 42, true);

    // Train the model using only the training data.
    // Uses stochastic gradient descent for 2000 epochs.
    model.fit_stochastic_gradient_descent(
        split.train_x,
        split.train_y,
        0.001,
        2000,
        42
    );

    // Display the number of observations in each dataset.
    std::cout << "Training observations = "
              << split.train_x.size()
              << ", testing observations = "
              << split.test_x.size() << "\n";

    // Predict the output for the first unseen testing input.
    std::cout << "Test prediction for first held-out value = "
              << model.predict(split.test_x.front()) << "\n";

    return 0;
}
