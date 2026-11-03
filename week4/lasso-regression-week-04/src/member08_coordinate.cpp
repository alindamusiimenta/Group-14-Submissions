#include "lasso/week2.hpp"
#include <cmath>
#include <stdexcept>

namespace lasso {

LassoFit coordinate_descent(const Matrix& features, const Vector& target,
                           double lambda, int max_passes, double tolerance) {
    if (features.empty() || features.size() != target.size())
        throw std::invalid_argument("invalid training data: feature rows and targets must match");
    if (lambda < 0.0 || !std::isfinite(lambda) || max_passes <= 0 ||
        tolerance <= 0.0 || !std::isfinite(tolerance))
        throw std::invalid_argument("lambda, max_passes, or tolerance is invalid");
    const std::size_t rows = features.size();
    const std::size_t columns = features[0].size();
    if (columns == 0) throw std::invalid_argument("training data must contain at least one feature");
    Vector coefficients(columns, 0.0);
    double intercept = 0.0;
    for (double value : target) intercept += value;
    intercept /= static_cast<double>(rows);
    for (const Vector& row : features) if (row.size() != columns) throw std::invalid_argument("rows must have equal sizes");

    int completed = 0;
    for (; completed < max_passes; ++completed) {
        double largest_change = 0.0;
        for (std::size_t column = 0; column < columns; ++column) {
            double residual_without_column = 0.0;
            double squared_column = 0.0;
            for (std::size_t row = 0; row < rows; ++row) {
                double prediction_without_column = 0.0;
                for (std::size_t other = 0; other < columns; ++other)
                    if (other != column) prediction_without_column += features[row][other] * coefficients[other];
                prediction_without_column += intercept;
                residual_without_column += features[row][column] * (target[row] - prediction_without_column);
                squared_column += features[row][column] * features[row][column];
            }
            if (squared_column == 0.0) continue;
            const double old_value = coefficients[column];
            coefficients[column] = soft_threshold(residual_without_column / rows, lambda) / (squared_column / rows);
            const double change = std::abs(coefficients[column] - old_value);
            if (change > largest_change) largest_change = change;
        }
        double updated_intercept = 0.0;
        for (std::size_t row = 0; row < rows; ++row)
            updated_intercept += target[row] - dot(features[row], coefficients);
        updated_intercept /= static_cast<double>(rows);
        const double intercept_change = std::abs(updated_intercept - intercept);
        intercept = updated_intercept;
        if (intercept_change > largest_change) largest_change = intercept_change;
        if (largest_change < tolerance) break;
    }

    double squared_error = 0.0;
    for (std::size_t row = 0; row < rows; ++row) {
        const double error = intercept + dot(features[row], coefficients) - target[row];
        squared_error += error * error;
    }
    double penalty = 0.0;
    for (double coefficient : coefficients) penalty += std::abs(coefficient);
    const double cost = squared_error / (2.0 * static_cast<double>(rows)) + lambda * penalty;
    return {coefficients, intercept, cost, completed + 1};
}

} // namespace lasso
