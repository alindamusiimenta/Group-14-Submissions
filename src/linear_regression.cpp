#include "linreg/linear_regression.hpp"

// This file contains the actual calculations declared in linear_regression.hpp.
// The model is a one-feature straight line: predicted_y = intercept + slope*x.

#include <cmath>
#include <algorithm>
#include <numeric>
#include <random>
#include <limits>
#include <stdexcept>
#include <string>

namespace linreg {
namespace {
// Shared input validation: x and y must have matching lengths, at least
// two observations, and no NaN or infinite values.
void validate_pairs(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) throw std::invalid_argument("input vectors must have equal lengths");
    if (a.size() < 2) throw std::invalid_argument("at least two observations are required");
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (!std::isfinite(a[i]) || !std::isfinite(b[i])) {
            throw std::invalid_argument("input values must be finite");
        }
    }
}

void validate_nonnegative(double value, const char* name) {
    if (!(value > 0.0) || !std::isfinite(value)) throw std::invalid_argument(std::string(name) + " must be positive and finite");
}
} // namespace

// CLOSED-FORM LEAST SQUARES
// Finds the slope and intercept directly from the training observations.
FitResult LinearRegression::fit_closed_form(const std::vector<double>& x, const std::vector<double>& y) {
    validate_pairs(x, y);
    // First calculate the average input and target values.
    const double mean_x = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
    const double mean_y = std::accumulate(y.begin(), y.end(), 0.0) / y.size();
    // The slope is numerator / denominator:
    // numerator   = sum((x - mean_x) * (y - mean_y))
    // denominator = sum((x - mean_x)^2)
    double numerator = 0.0, denominator = 0.0;
    for (std::size_t i = 0; i < x.size(); ++i) {
        numerator += (x[i] - mean_x) * (y[i] - mean_y);
        denominator += (x[i] - mean_x) * (x[i] - mean_x);
    }
    if (denominator == 0.0) throw std::invalid_argument("x must contain at least two distinct values");
    // Calculate the slope of the best-fit straight line.
    slope_ = numerator / denominator;
    // Calculate the intercept; the fitted line passes through (mean_x, mean_y).
    intercept_ = mean_y - slope_ * mean_x;
    fitted_ = true;
    const auto predictions = predict(x);
    return {intercept_, slope_, mean_squared_error(y, predictions), r_squared(y, predictions), 1};
}

// BATCH GRADIENT DESCENT
// Repeatedly adjusts both parameters using errors from the whole dataset.
FitResult LinearRegression::fit_gradient_descent(const std::vector<double>& x, const std::vector<double>& y,
                                                  double learning_rate, std::size_t iterations) {
    validate_pairs(x, y);
    validate_nonnegative(learning_rate, "learning_rate");
    if (iterations == 0) throw std::invalid_argument("iterations must be greater than zero");
    intercept_ = 0.0; slope_ = 0.0;
    const double n = static_cast<double>(x.size());
    // Each iteration calculates the gradient using every training observation.
    for (std::size_t step = 0; step < iterations; ++step) {
        double d_intercept = 0.0, d_slope = 0.0;
        for (std::size_t i = 0; i < x.size(); ++i) {
            const double error = (intercept_ + slope_ * x[i]) - y[i];
            d_intercept += error;
            d_slope += error * x[i];
        }
        // Move parameters opposite the gradient to reduce mean squared error.
        // The learning rate controls the size of each parameter update.
        intercept_ -= learning_rate * 2.0 * d_intercept / n;
        slope_ -= learning_rate * 2.0 * d_slope / n;
    }
    fitted_ = true;
    const auto predictions = predict(x);
    return {intercept_, slope_, mean_squared_error(y, predictions), r_squared(y, predictions), iterations};
}

// STOCHASTIC GRADIENT DESCENT
// Updates the model after each individual observation rather than after
// processing the complete dataset.
FitResult LinearRegression::fit_stochastic_gradient_descent(const std::vector<double>& x,
                                                             const std::vector<double>& y,
                                                             double learning_rate,
                                                             std::size_t epochs,
                                                             unsigned seed) {
    validate_pairs(x, y);
    validate_nonnegative(learning_rate, "learning_rate");
    if (epochs == 0) throw std::invalid_argument("epochs must be greater than zero");

    intercept_ = 0.0;
    slope_ = 0.0;
    std::vector<std::size_t> order(x.size());
    std::iota(order.begin(), order.end(), 0);
    // A fixed seed makes the shuffle sequence reproducible for testing.
    std::mt19937 generator(seed);

    for (std::size_t epoch = 0; epoch < epochs; ++epoch) {
        // Shuffle the observation order at the start of each epoch.
        std::shuffle(order.begin(), order.end(), generator);
        for (const std::size_t index : order) {
            const double error = (intercept_ + slope_ * x[index]) - y[index];
            intercept_ -= learning_rate * 2.0 * error;
            slope_ -= learning_rate * 2.0 * error * x[index];
        }
    }
    fitted_ = true;
    const auto predictions = predict(x);
    return {intercept_, slope_, mean_squared_error(y, predictions), r_squared(y, predictions), epochs};
}

// PREDICTION: apply y_hat = intercept + slope*x to a new input value.
double LinearRegression::predict(double x) const {
    if (!fitted_) throw std::logic_error("fit the model before making predictions");
    if (!std::isfinite(x)) throw std::invalid_argument("prediction input must be finite");
    return intercept_ + slope_ * x;
}
std::vector<double> LinearRegression::predict(const std::vector<double>& x) const {
    std::vector<double> result;
    result.reserve(x.size());
    for (double value : x) result.push_back(predict(value));
    return result;
}

// MSE is the average squared difference between actual and predicted values.
// Smaller MSE means predictions are closer to the actual values.
double mean_squared_error(const std::vector<double>& actual, const std::vector<double>& predicted) {
    validate_pairs(actual, predicted);
    double sum = 0.0;
    for (std::size_t i = 0; i < actual.size(); ++i) sum += std::pow(actual[i] - predicted[i], 2);
    return sum / actual.size();
}

// R-squared measures how much of the target variation is explained by the model.
// A value closer to 1 generally indicates a better fit on the evaluated data.
double r_squared(const std::vector<double>& actual, const std::vector<double>& predicted) {
    validate_pairs(actual, predicted);
    const double mean = std::accumulate(actual.begin(), actual.end(), 0.0) / actual.size();
    double ss_res = 0.0, ss_tot = 0.0;
    for (std::size_t i = 0; i < actual.size(); ++i) {
        ss_res += std::pow(actual[i] - predicted[i], 2);
        ss_tot += std::pow(actual[i] - mean, 2);
    }
    if (ss_tot == 0.0) throw std::invalid_argument("actual values must not all be identical");
    return 1.0 - ss_res / ss_tot;
}

// Pearson correlation measures the strength and direction of a linear
// relationship between the input x and target y.
double correlation_coefficient(const std::vector<double>& x, const std::vector<double>& y) {
    validate_pairs(x, y);
    const double mean_x = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
    const double mean_y = std::accumulate(y.begin(), y.end(), 0.0) / y.size();
    double numerator = 0.0, sum_x = 0.0, sum_y = 0.0;
    for (std::size_t i = 0; i < x.size(); ++i) {
        const double dx = x[i] - mean_x, dy = y[i] - mean_y;
        numerator += dx * dy; sum_x += dx * dx; sum_y += dy * dy;
    }
    if (sum_x == 0.0 || sum_y == 0.0) throw std::invalid_argument("correlation is undefined for constant data");
    return numerator / std::sqrt(sum_x * sum_y);
}

// Estimates the typical size of residual errors, adjusted for model parameters.
double standard_error_of_estimate(const std::vector<double>& actual, const std::vector<double>& predicted,
                                  std::size_t number_of_parameters) {
    validate_pairs(actual, predicted);
    if (actual.size() <= number_of_parameters) throw std::invalid_argument("not enough observations for standard error");
    double residual_sum = 0.0;
    for (std::size_t i = 0; i < actual.size(); ++i) residual_sum += std::pow(actual[i] - predicted[i], 2);
    return std::sqrt(residual_sum / (actual.size() - number_of_parameters));
}

// TRAIN/TEST SPLIT: divide observations while keeping each x paired with y.
// Training data fits the model; testing data evaluates unseen observations.
DatasetSplit train_test_split(const std::vector<double>& x, const std::vector<double>& y,
                              double test_fraction, unsigned seed, bool shuffle) {
    validate_pairs(x, y);
    if (!std::isfinite(test_fraction) || test_fraction <= 0.0 || test_fraction >= 1.0) {
        throw std::invalid_argument("test_fraction must be between zero and one");
    }

    std::vector<std::size_t> order(x.size());
    std::iota(order.begin(), order.end(), 0);
    if (shuffle) {
        std::mt19937 generator(seed);
        std::shuffle(order.begin(), order.end(), generator);
    }
    // Round up the test count, while keeping at least one training observation.
    std::size_t test_count = static_cast<std::size_t>(std::ceil(test_fraction * x.size()));
    test_count = std::max<std::size_t>(1, std::min(test_count, x.size() - 1));
    DatasetSplit split;
    split.test_x.reserve(test_count);
    split.test_y.reserve(test_count);
    split.train_x.reserve(x.size() - test_count);
    split.train_y.reserve(x.size() - test_count);
    for (std::size_t position = 0; position < order.size(); ++position) {
        const auto index = order[position];
        if (position < test_count) {
            split.test_x.push_back(x[index]);
            split.test_y.push_back(y[index]);
        } else {
            split.train_x.push_back(x[index]);
            split.train_y.push_back(y[index]);
        }
    }
    return split;
}
} // namespace linreg
