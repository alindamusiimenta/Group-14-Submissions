#include "lasso/week3.hpp"
#include <cmath>
#include <stdexcept>

namespace lasso {

double mean_absolute_error(const Vector& actual, const Vector& predicted) {
    if (actual.size() != predicted.size() || actual.empty()) throw std::invalid_argument("prediction vectors must match");
    double total = 0.0;
    for (std::size_t i = 0; i < actual.size(); ++i) total += std::abs(actual[i] - predicted[i]);
    return total / actual.size();
}

} // namespace lasso

// Week 3 continuation: report several regression metrics.
#include <cmath>
#include <stdexcept>
namespace lasso {
RegressionMetrics evaluate_regression(const Vector& actual, const Vector& predicted) {
    if (actual.empty() || actual.size() != predicted.size()) throw std::invalid_argument("metric vectors must match");
    double absolute = 0.0, squared = 0.0, actual_mean = 0.0;
    for (double value : actual) actual_mean += value;
    actual_mean /= actual.size();
    double total_variation = 0.0;
    for (std::size_t i = 0; i < actual.size(); ++i) {
        const double error = actual[i] - predicted[i];
        absolute += std::abs(error);
        squared += error * error;
        const double difference = actual[i] - actual_mean;
        total_variation += difference * difference;
    }
    const double mse = squared / actual.size();
    const double r_squared = total_variation == 0.0 ? 0.0 : 1.0 - squared / total_variation;
    return {absolute / actual.size(), mse, std::sqrt(mse), r_squared};
}
} // namespace lasso
