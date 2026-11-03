#include "lasso/week3.hpp" // includes definitions of matrix, vector and dot

#include <cmath>
#include <stdexcept> // provides std::invalid_argument for reporting invalid input

namespace lasso {

Vector multiply_rows(const Matrix& matrix, const Vector& values) {
    Vector result;
    result.reserve(matrix.size());

    for (const Vector& row : matrix) {
        if (row.size() != values.size()) {
            throw std::invalid_argument("matrix row and vector must have the same size");
        }
        result.push_back(dot(row, values));
    }
    return result;// returns one calculated value for each matrix row
}

Vector predict_rows(const Matrix& features, const Vector& coefficients, double intercept) {
    if (features.empty() || coefficients.empty() || !std::isfinite(intercept)) {
        throw std::invalid_argument("features, coefficients, and intercept must be valid");
    }

    Vector predictions;// stores predicted value per observation
    predictions.reserve(features.size());// each row represents one observation and contains its eature values
    for (const Vector& row : features) {
        if (row.size() != coefficients.size()) {
            throw std::invalid_argument("feature width and coefficient count must match");
        }
        predictions.push_back(intercept + dot(row, coefficients));
    }
    return predictions;// returns predicted target value for ever observation
}

} // namespace lasso
