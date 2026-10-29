#include "lasso/week2.hpp"

#include <cmath>
#include <stdexcept>

namespace lasso {

LassoFit coordinate_descent(const Matrix& features, const Vector& target,
                            double lambda, int max_passes, double tolerance) {
    check_preprocessing_input(features, target);
    if (lambda < 0.0 || !std::isfinite(lambda) || max_passes <= 0 ||
        tolerance <= 0.0 || !std::isfinite(tolerance)) {
        throw std::invalid_argument("lambda, max passes, or tolerance is invalid");
    }

    const std::size_t row_count = features.size();
    const std::size_t column_count = features[0].size();
    Vector coefficients(column_count, 0.0);

    double intercept = 0.0;
    for (double value : target) {
        intercept += value;
    }
    intercept /= static_cast<double>(row_count);

    int passes_used = 0;
    for (int pass = 0; pass < max_passes; ++pass) {
        passes_used = pass + 1;
        double largest_change = 0.0;

        for (std::size_t column = 0; column < column_count; ++column) {
            double residual_total = 0.0;
            double squared_feature_total = 0.0;

            for (std::size_t row = 0; row < row_count; ++row) {
                double prediction_without_column = intercept;
                for (std::size_t other = 0; other < column_count; ++other) {
                    if (other != column) {
                        prediction_without_column += features[row][other] * coefficients[other];
                    }
                }

                const double residual = target[row] - prediction_without_column;
                residual_total += features[row][column] * residual;
                squared_feature_total += features[row][column] * features[row][column];
            }

            if (squared_feature_total == 0.0) {
                coefficients[column] = 0.0;
                continue;
            }

            const double old_coefficient = coefficients[column];
            const double average_residual = residual_total / static_cast<double>(row_count);
            const double average_square = squared_feature_total / static_cast<double>(row_count);
            coefficients[column] = soft_threshold(average_residual, lambda) / average_square;

            const double coefficient_change = std::abs(coefficients[column] - old_coefficient);
            if (coefficient_change > largest_change) {
                largest_change = coefficient_change;
            }
        }

        double updated_intercept = 0.0;
        for (std::size_t row = 0; row < row_count; ++row) {
            updated_intercept += target[row] - dot(features[row], coefficients);
        }
        updated_intercept /= static_cast<double>(row_count);

        const double intercept_change = std::abs(updated_intercept - intercept);
        if (intercept_change > largest_change) {
            largest_change = intercept_change;
        }
        intercept = updated_intercept;

        if (largest_change < tolerance) {
            break;
        }
    }

    double squared_error = 0.0;
    for (std::size_t row = 0; row < row_count; ++row) {
        const double prediction = intercept + dot(features[row], coefficients);
        const double error = prediction - target[row];
        squared_error += error * error;
    }

    double penalty = 0.0;
    for (double coefficient : coefficients) {
        penalty += std::abs(coefficient);
    }

    const double cost = squared_error / (2.0 * static_cast<double>(row_count)) + lambda * penalty;
    return {coefficients, intercept, cost, passes_used};
}

} // namespace lasso
