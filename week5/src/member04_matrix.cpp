#include "lasso/week3.hpp"

#include <cmath>
#include <stdexcept>

namespace lasso {

// Computes the matrix-vector product, returning one value per row.
Vector multiply_rows(const Matrix& matrix, const Vector& values) {
    Vector result;
    result.reserve(matrix.size());

    for (const Vector& row : matrix) {
        if (row.size() != values.size()) {
            throw std::invalid_argument(
                "matrix row and vector must have the same size");
        }

        result.push_back(dot(row, values));
    }

    return result;
}

// Predicts one target value for every feature row.
Vector predict_rows(const Matrix& features,
                    const Vector& coefficients,
                    double intercept) {

    if (features.empty() ||
        coefficients.empty() ||
        !std::isfinite(intercept)) {
        throw std::invalid_argument(
            "features, coefficients, and intercept must be valid");
    }

    Vector predictions;
    predictions.reserve(features.size());

    for (const Vector& row : features) {
        if (row.size() != coefficients.size()) {
            throw std::invalid_argument(
                "feature width and coefficient count must match");
        }

        predictions.push_back(
            intercept + dot(row, coefficients));
    }

    return predictions;
}

} // namespace lasso