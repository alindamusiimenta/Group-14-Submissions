#include "lasso/week3.hpp" // header povides vector and matrix types
#include <stdexcept>

namespace lasso {

Vector multiply_rows(const Matrix& matrix, const Vector& values) {
    Vector result; //will old one output number per row
    for (const Vector& row : matrix) {
        if (row.size() != values.size()) throw std::invalid_argument("matrix row and vector must match");// a dot prouct only works whe both vectors are the same length
        double total = 0.0;
        for (std::size_t i = 0; i < row.size(); ++i) total += row[i] * values[i];
        result.push_back(total);
    }
    return result;
}

} // namespace lasso

// Week 3 continuation: make one prediction for every feature row.
#include <stdexcept>
namespace lasso {
Vector predict_rows(const Matrix& features, const Vector& coefficients, double intercept) {
    Vector predictions; // will hold one prediction per sample
    for (const Vector& row : features) {
        if (row.size() != coefficients.size()) throw std::invalid_argument("feature width and coefficients must match");
        double prediction = intercept;
        for (std::size_t column = 0; column < row.size(); ++column) prediction += row[column] * coefficients[column];
        predictions.push_back(prediction); // store this samples's prediction
    }
    return predictions;
}
} // namespace lasso
