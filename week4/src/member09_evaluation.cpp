#include "lasso/week3.hpp"

#include <cmath>
#include <stdexcept>

namespace lasso {

RegressionMetrics evaluate_regression(const Vector& actual, const Vector& predicted) {
    if (actual.empty() || actual.size() != predicted.size()) {
        throw std::invalid_argument("metric vectors must have equal non-empty sizes");
    }

    double actual_mean = 0.0;
    for (std::size_t index = 0; index < actual.size(); ++index) {
        if (!std::isfinite(actual[index]) || !std::isfinite(predicted[index])) {
            throw std::invalid_argument("metric values must be finite");
        }
        actual_mean += actual[index];
    }
    actual_mean /= static_cast<double>(actual.size());

    double absolute_error_total = 0.0;
    double squared_error_total = 0.0;
    double total_variation = 0.0;
    for (std::size_t index = 0; index < actual.size(); ++index) {
        const double error = actual[index] - predicted[index];
        absolute_error_total += std::abs(error);
        squared_error_total += error * error;

        const double difference_from_mean = actual[index] - actual_mean;
        total_variation += difference_from_mean * difference_from_mean;
    }

    const double mse = squared_error_total / static_cast<double>(actual.size());
    const double r_squared = total_variation == 0.0
        ? 0.0
        : 1.0 - squared_error_total / total_variation;

    return {
        absolute_error_total / static_cast<double>(actual.size()),
        mse,
        std::sqrt(mse),
        r_squared
    };
}

double mean_absolute_error(const Vector& actual, const Vector& predicted) {
    return evaluate_regression(actual, predicted).mae;
}

} // namespace lasso
