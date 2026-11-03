#include "lasso/lasso_regression.hpp"

#include <cmath>
#include <stdexcept>

namespace lasso {

// Member 3: average of the values in one feature column.
double mean(const Vector& values) {
    if (values.empty()) {
        throw std::invalid_argument("cannot take the mean of no values");
    }
    double total = 0.0;
    for (double value : values) {
        total += value;
    }
    return total / static_cast<double>(values.size());
}

// Member 3: spread of one feature column (divides by n, not n - 1).
double standard_deviation(const Vector& values) {
    const double average = mean(values);
    double squared_total = 0.0;
    for (double value : values) {
        const double difference = value - average;
        squared_total += difference * difference;
    }
    return std::sqrt(squared_total / static_cast<double>(values.size()));
}

} // namespace lasso
