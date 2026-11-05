#include "lasso/week2.hpp"

#include <cmath>
#include <stdexcept>

namespace lasso {

LassoFit coordinate_descent(const Matrix& features,
                            const Vector& target,
                            double lambda,
                            int max_passes,
                            double tolerance) {

    // Validate training data.
    check_preprocessing_input(features, target);

    if (lambda < 0.0 || !std::isfinite(lambda) ||
        max_passes <= 0 ||
        tolerance <= 0.0 || !std::isfinite(tolerance)) {
        throw std::invalid_argument("invalid optimizer settings");
    }

    const std::size_t rows = features.size();
    const std::size_t columns = features[0].size();
    const double n = static_cast<double>(rows);

    // Initialize coefficients and intercept.
    Vector coefficients(columns, 0.0);

    double intercept = 0.0;

    for (double value : target) {
        intercept += value;
    }

    intercept /= n;

    int passes = 0;

    // Coordinate descent optimization.
    for (; passes < max_passes; ++passes) {

        double largest_change = 0.0;

        // Update the intercept.
        double old_intercept = intercept;
        double intercept_sum = 0.0;

        for (std::size_t row = 0; row < rows; ++row) {

            double prediction = 0.0;

            for (std::size_t column = 0;
                 column < columns; ++column) {
                prediction +=
                    features[row][column] * coefficients[column];
            }

            intercept_sum += target[row] - prediction;
        }

        intercept = intercept_sum / n;

        largest_change = std::abs(intercept - old_intercept);

        // Update each coefficient individually.
        for (std::size_t column = 0;
             column < columns; ++column) {

            double residual_without_column = 0.0;
            double squared_column = 0.0;

            for (std::size_t row = 0; row < rows; ++row) {

                double prediction_without_column = intercept;

                for (std::size_t other = 0;
                     other < columns; ++other) {

                    if (other != column) {
                        prediction_without_column +=
                            features[row][other] * coefficients[other];
                    }
                }

                residual_without_column +=
                    features[row][column] *
                    (target[row] - prediction_without_column);

                squared_column +=
                    features[row][column] * features[row][column];
            }

            if (squared_column == 0.0) {
                continue;
            }

            const double old_value = coefficients[column];

            coefficients[column] =
                soft_threshold(residual_without_column / n, lambda) /
                (squared_column / n);

            const double change =
                std::abs(coefficients[column] - old_value);

            if (change > largest_change) {
                largest_change = change;
            }
        }

        // Stop when the largest parameter change is sufficiently small.
        if (largest_change < tolerance) {
            ++passes;
            break;
        }
    }

    // Calculate cost using the fitted intercept.
    const double cost =
        lasso_cost(features, target, coefficients, lambda, intercept);

    // LassoFit field order:
    // coefficients, intercept, cost, passes.
    return {coefficients, intercept, cost, passes};
}

} // namespace lasso
