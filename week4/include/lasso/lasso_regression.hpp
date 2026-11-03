#pragma once

#include <string>
#include <vector>

namespace lasso {

using Vector = std::vector<double>; // One row or one set of values.
using Matrix = std::vector<Vector>; // A list of feature rows.

struct Dataset {
    Matrix features;
    Vector target;
};

// Multiply matching positions in two vectors and add the results.
double dot(const Vector& left, const Vector& right);

// Multiply every matrix row by one vector.
Vector matrix_vector_product(const Matrix& matrix, const Vector& vector);

// Shrink a value toward zero by the supplied non-negative threshold.
double soft_threshold(double value, double threshold);

// Calculate squared-error cost plus the L1 penalty for a coefficient vector.
double lasso_cost(const Matrix& features, const Vector& target,
                  const Vector& coefficients, double lambda);

// Reads a CSV whose first column is the target and remaining columns are features.
Dataset load_csv(const std::string& path, bool has_header = true);

} // namespace lasso
