// lasso_regression.cpp
// Core LASSO helpers: vector/matrix maths, soft-thresholding, the LASSO cost
// function and a CSV loader. Public declarations live in lasso/lasso_regression.hpp.
#include "lasso/lasso_regression.hpp"

#include <cmath>
#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace lasso {
// Anonymous namespace: these helpers are private to this file.
namespace {

// Validates a feature matrix and its target vector before any maths is done.
// Throws std::invalid_argument if the data is empty, mismatched, ragged
// (rows of different lengths) or contains NaN/infinity.
void check_matrix_and_target(const Matrix& features, const Vector& target) {
    // There must be at least one row, and one target value per row.
    if (features.empty() || features.size() != target.size()) {
        throw std::invalid_argument("feature rows and target values must match");
    }

    // The first row decides how many features every row must have.
    const std::size_t column_count = features[0].size();
    if (column_count == 0) {
        throw std::invalid_argument("each row must contain at least one feature");
    }

    for (std::size_t row_index = 0; row_index < features.size(); ++row_index) {
        // Every row must have the same number of values as the first row.
        if (features[row_index].size() != column_count) {
            throw std::invalid_argument("all feature rows must have the same number of values");
        }
        // Reject NaN and infinity in the features.
        for (double value : features[row_index]) {
            if (!std::isfinite(value)) {
                throw std::invalid_argument("feature values must be finite numbers");
            }
        }
        // The matching target value must also be a finite number.
        if (!std::isfinite(target[row_index])) {
            throw std::invalid_argument("target values must be finite numbers");
        }
    }
}

// Converts one CSV cell (text) into a double.
// Accepts only a complete, finite number; trailing spaces are allowed.
double parse_number(const std::string& cell) {
    std::size_t characters_used = 0;
    double value = 0.0;

    // std::stod throws on text such as "abc"; turn that into our own error.
    try {
        value = std::stod(cell, &characters_used);
    } catch (const std::exception&) {
        throw std::invalid_argument("CSV cells must contain numbers");
    }

    // Skip trailing whitespace so "3.5 " counts as valid.
    while (characters_used < cell.size() &&
           std::isspace(static_cast<unsigned char>(cell[characters_used]))) {
        ++characters_used;
    }

    // If anything is left over (for example "3.5abc") or the value is
    // NaN/infinity, the cell is not a clean number.
    if (characters_used != cell.size() || !std::isfinite(value)) {
        throw std::invalid_argument("CSV cells must contain finite numbers only");
    }
    return value;
}

} // namespace

// Dot product of two vectors: sum of left[i] * right[i].
// Both vectors must have the same length.
double dot(const Vector& left, const Vector& right) {
    if (left.size() != right.size()) {
        throw std::invalid_argument("dot-product vectors must have the same size");
    }

    double answer = 0.0;
    for (std::size_t index = 0; index < left.size(); ++index) {
        answer += left[index] * right[index];
    }
    return answer;
}

// Multiplies a matrix by a vector. Result[i] is row i of the matrix dotted
// with the vector, so this computes the predictions X * beta.
Vector matrix_vector_product(const Matrix& matrix, const Vector& vector) {
    Vector result;
    // One output value per matrix row, so reserve the space once.
    result.reserve(matrix.size());

    for (const Vector& row : matrix) {
        result.push_back(dot(row, vector));
    }
    return result;
}

// Soft-thresholding operator, the key step of LASSO coefficient shrinkage:
//   value >  threshold  ->  value - threshold
//   value < -threshold  ->  value + threshold
//   otherwise           ->  0   (the coefficient is set exactly to zero)
double soft_threshold(double value, double threshold) {
    // Both inputs must be finite and the threshold cannot be negative.
    if (!std::isfinite(value) || !std::isfinite(threshold) || threshold < 0.0) {
        throw std::invalid_argument("value must be finite and threshold must be non-negative and finite");
    }

    if (value > threshold) {
        return value - threshold;
    }
    if (value < -threshold) {
        return value + threshold;
    }
    return 0.0;
}

// LASSO cost (objective) function:
//   cost = (1 / (2n)) * sum((prediction - target)^2) + lambda * sum(|beta_j|)
// The first part is half the mean squared error; the second is the L1
// penalty that pushes coefficients towards zero. A bigger lambda means
// stronger shrinkage. There is no intercept term in this version.
double lasso_cost(const Matrix& features, const Vector& target,
                  const Vector& coefficients, double lambda) {
    // Validate the data, then the coefficient count and lambda.
    check_matrix_and_target(features, target);
    if (coefficients.size() != features[0].size()) {
        throw std::invalid_argument("coefficient count must match feature count");
    }
    if (lambda < 0.0 || !std::isfinite(lambda)) {
        throw std::invalid_argument("lambda must be non-negative and finite");
    }

    // Part 1: add up the squared prediction error over all rows.
    double squared_error = 0.0;
    for (std::size_t row = 0; row < features.size(); ++row) {
        const double prediction = dot(features[row], coefficients);
        const double error = prediction - target[row];
        squared_error += error * error;
    }

    // Part 2: the L1 penalty is the sum of absolute coefficient values.
    double penalty = 0.0;
    for (double coefficient : coefficients) {
        penalty += std::abs(coefficient);
    }

    // Combine: mean squared error part (divided by 2n) plus lambda * penalty.
    return squared_error / (2.0 * static_cast<double>(features.size())) + lambda * penalty;
}

// Loads a dataset from a CSV file.
// Expected layout: the FIRST column is the target (y); every other column is
// a feature. Set has_header to true to skip a header row.
Dataset load_csv(const std::string& path, bool has_header) {
    std::ifstream file(path);
    if (!file) {
        throw std::invalid_argument("could not open CSV file: " + path);
    }

    Dataset dataset;
    std::string line;

    // Skip the header line if the file has one.
    if (has_header && !std::getline(file, line)) {
        throw std::invalid_argument("CSV file is empty");
    }

    // 0 means "not known yet"; it is set from the first data row.
    std::size_t expected_feature_count = 0;
    while (std::getline(file, line)) {
        // Ignore blank lines.
        if (line.empty()) {
            continue;
        }
        // A trailing comma would create an empty last cell, so reject it.
        if (line.back() == ',') {
            throw std::invalid_argument("CSV rows cannot end with an empty cell");
        }

        // Split the line on commas and convert each cell to a number.
        std::stringstream row_stream(line);
        std::string cell;
        Vector values;
        while (std::getline(row_stream, cell, ',')) {
            values.push_back(parse_number(cell));
        }

        // Each row needs one target plus at least one feature.
        if (values.size() < 2) {
            throw std::invalid_argument("each CSV row needs a target and at least one feature");
        }

        // All rows must have the same number of features as the first row.
        const std::size_t feature_count = values.size() - 1;
        if (expected_feature_count == 0) {
            expected_feature_count = feature_count;
        } else if (feature_count != expected_feature_count) {
            throw std::invalid_argument("CSV rows must have the same number of columns");
        }

        // First value is the target; the rest are the features for this row.
        dataset.target.push_back(values[0]);
        dataset.features.emplace_back(values.begin() + 1, values.end());
    }

    // A file with only a header (or nothing) has no usable data.
    if (dataset.features.empty()) {
        throw std::invalid_argument("CSV file has no data rows");
    }
    return dataset;
}

} // namespace lasso