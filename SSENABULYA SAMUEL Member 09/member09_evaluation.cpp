#include "lasso/week2.hpp"
#include <cmath>
#include <stdexcept>

namespace lasso {

double mean_absolute_error(const Vector& actual, const Vector& predicted) {

    // Ensure both vectors have the same size and are not empty
    if (actual.size() != predicted.size() || actual.empty()) throw std::invalid_argument("prediction vectors must match");
    double total = 0.0;

    // Accumulate the absolute differences between actual and predicted values
    for (std::size_t i = 0; i < actual.size(); ++i) total += std::abs(actual[i] - predicted[i]);

    // Return the average error by dividing the total absolute error by the number of elements
    return total / actual.size();
}

} // namespace lasso
