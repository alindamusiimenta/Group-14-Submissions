
#pragma once

#include <cstddef>  // Provides std::size_t for counting iterations and observations.
#include <vector>   // Provides std::vector for storing input and output data.

namespace linreg {

// Stores the results obtained after training a linear regression model.
struct FitResult {
    double intercept{};       // Constant term (c) in the equation y = c + mx.
    double slope{};           // Gradient (m), showing how y changes with x.
    double mse{};             // Mean Squared Error: measures prediction error.
    double r_squared{};       // R-squared: measures how well the model fits the data.
    std::size_t iterations{}; // Number of training iterations or epochs completed.
};

// Stores training and testing data after splitting a dataset.
struct DatasetSplit {
    std::vector<double> train_x; // Input values used to train the model.
    std::vector<double> train_y; // Actual target values used during training.
    std::vector<double> test_x;  // Input values reserved for testing.
    std::vector<double> test_y;  // Actual target values used to evaluate predictions.
};

// Main class responsible for building and using a linear regression model.
class LinearRegression {
public:
    // Trains the model using the closed-form least-squares method.
    // It calculates the best-fit intercept and slope directly from the data.
    // Model equation: y = intercept + slope*x.
    FitResult fit_closed_form(const std::vector<double>& x,
                              const std::vector<double>& y);

    // Trains the model using batch gradient descent.
    // The algorithm repeatedly adjusts the intercept and slope
    // to reduce the prediction error across the entire dataset.
    // learning_rate controls the size of each parameter update.
    // iterations determines how many updates are performed.
    FitResult fit_gradient_descent(const std::vector<double>& x,
                                   const std::vector<double>& y,
                                   double learning_rate = 0.01,
                                   std::size_t iterations = 1000);

    // Trains the model using stochastic gradient descent (SGD).
    // Unlike batch gradient descent, SGD updates the model
    // using one randomly selected observation at a time.
    // epochs determines how many complete passes are made through the data.
    // seed makes the random shuffling reproducible.
    FitResult fit_stochastic_gradient_descent(const std::vector<double>& x,
                                              const std::vector<double>& y,
                                              double learning_rate = 0.001,
                                              std::size_t epochs = 1000,
                                              unsigned seed = 42);

    // Predicts the target value for one input value.
    // Uses the trained equation: y = intercept + slope*x.
    [[nodiscard]] double predict(double x) const;

    // Predicts target values for several input values.
    // Returns a vector containing one prediction for each input.
    [[nodiscard]] std::vector<double> predict(const std::vector<double>& x) const;

    // Returns the intercept (constant term) of the trained model.
    [[nodiscard]] double intercept() const noexcept { return intercept_; }

    // Returns the slope (gradient) of the trained model.
    [[nodiscard]] double slope() const noexcept { return slope_; }

private:
    // These variables store the parameters learned during training.
    double intercept_{0.0}; // Initial intercept is zero.
    double slope_{0.0};     // Initial slope is zero.

    // Tracks whether the model has been trained before making predictions.
    bool fitted_{false};
};

// Calculates Mean Squared Error (MSE).
// It measures the average squared difference between actual and predicted values.
// A smaller MSE generally indicates more accurate predictions.
[[nodiscard]] double mean_squared_error(const std::vector<double>& actual,
                                         const std::vector<double>& predicted);

// Calculates the coefficient of determination (R-squared).
// It indicates how much of the variation in the actual data
// is explained by the regression model.
[[nodiscard]] double r_squared(const std::vector<double>& actual,
                               const std::vector<double>& predicted);

// Calculates the Pearson correlation coefficient between x and y.
// It measures the strength and direction of their linear relationship.
// Its value ranges from -1 to +1.
[[nodiscard]] double correlation_coefficient(const std::vector<double>& x,
                                             const std::vector<double>& y);

// Calculates the standard error of the estimate.
// It measures the typical difference between actual and predicted values.
// number_of_parameters represents the number of fitted model parameters.
[[nodiscard]] double standard_error_of_estimate(const std::vector<double>& actual,
                                                const std::vector<double>& predicted,
                                                std::size_t number_of_parameters = 2);

// Splits the input and target data into training and testing sets.
// The input x and target y are kept paired during the split.
// test_fraction controls the proportion of data reserved for testing.
// seed allows the same random split to be reproduced.
// shuffle determines whether the observations are randomly rearranged.
DatasetSplit train_test_split(const std::vector<double>& x,
                              const std::vector<double>& y,
                              double test_fraction = 0.2,
                              unsigned seed = 42,
                              bool shuffle = true);

} // namespace linreg
