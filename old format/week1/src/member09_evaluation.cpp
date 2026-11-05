#include "lasso/lasso_regression.hpp"

#include <stdexcept>

namespace lasso {

// Member 9: average of the squared differences between actual and predicted.
double mean_squared_error(const Vector& actual, const Vector& predicted) {
    if (actual.empty() || actual.size() != predicted.size()) {
        throw std::invalid_argument("MSE vectors must have equal non-empty sizes");
    }
    double total = 0.0;
    for (std::size_t i = 0; i < actual.size(); ++i) {
        const double error = actual[i] - predicted[i];
        total += error * error;
    }
    return total / static_cast<double>(actual.size());
}

} // namespace lasso
