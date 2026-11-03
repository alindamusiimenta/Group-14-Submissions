#include "lasso/lasso_regression.hpp"

#include <cmath>
#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace lasso {
namespace {

void check_matrix_and_target(const Matrix& features, const Vector& target) {
    if (features.empty() || features.size() != target.size()) {
        throw std::invalid_argument("feature rows and target values must match");
    }

    const std::size_t column_count = features[0].size();
    if (column_count == 0) {
        throw std::invalid_argument("each row must contain at least one feature");
    }

    for (std::size_t row_index = 0; row_index < features.size(); ++row_index) {
        if (features[row_index].size() != column_count) {
            throw std::invalid_argument("all feature rows must have the same number of values");
        }
        for (double value : features[row_index]) {
            if (!std::isfinite(value)) {
                throw std::invalid_argument("feature values must be finite numbers");
            }
        }
        if (!std::isfinite(target[row_index])) {
            throw std::invalid_argument("target values must be finite numbers");
        }
    }
}

double parse_number(const std::string& cell) {
    std::size_t characters_used = 0;
    double value = 0.0;

    try {
        value = std::stod(cell, &characters_used);
    } catch (const std::exception&) {
        throw std::invalid_argument("CSV cells must contain numbers");
    }

    while (characters_used < cell.size() &&
           std::isspace(static_cast<unsigned char>(cell[characters_used]))) {
        ++characters_used;
    }

    if (characters_used != cell.size() || !std::isfinite(value)) {
        throw std::invalid_argument("CSV cells must contain finite numbers only");
    }
    return value;
}

} // namespace

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

Vector matrix_vector_product(const Matrix& matrix, const Vector& vector) {
    Vector result;
    result.reserve(matrix.size());

    for (const Vector& row : matrix) {
        result.push_back(dot(row, vector));
    }
    return result;
}

double soft_threshold(double value, double threshold) {
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

double lasso_cost(const Matrix& features, const Vector& target,
                  const Vector& coefficients, double lambda) {
    check_matrix_and_target(features, target);
    if (coefficients.size() != features[0].size()) {
        throw std::invalid_argument("coefficient count must match feature count");
    }
    if (lambda < 0.0 || !std::isfinite(lambda)) {
        throw std::invalid_argument("lambda must be non-negative and finite");
    }

    double squared_error = 0.0;
    for (std::size_t row = 0; row < features.size(); ++row) {
        const double prediction = dot(features[row], coefficients);
        const double error = prediction - target[row];
        squared_error += error * error;
    }

    double penalty = 0.0;
    for (double coefficient : coefficients) {
        penalty += std::abs(coefficient);
    }

    return squared_error / (2.0 * static_cast<double>(features.size())) + lambda * penalty;
}

Dataset load_csv(const std::string& path, bool has_header) {
    std::ifstream file(path);
    if (!file) {
        throw std::invalid_argument("could not open CSV file: " + path);
    }

    Dataset dataset;
    std::string line;

    if (has_header && !std::getline(file, line)) {
        throw std::invalid_argument("CSV file is empty");
    }

    std::size_t expected_feature_count = 0;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        if (line.back() == ',') {
            throw std::invalid_argument("CSV rows cannot end with an empty cell");
        }

        std::stringstream row_stream(line);
        std::string cell;
        Vector values;
        while (std::getline(row_stream, cell, ',')) {
            values.push_back(parse_number(cell));
        }

        if (values.size() < 2) {
            throw std::invalid_argument("each CSV row needs a target and at least one feature");
        }

        const std::size_t feature_count = values.size() - 1;
        if (expected_feature_count == 0) {
            expected_feature_count = feature_count;
        } else if (feature_count != expected_feature_count) {
            throw std::invalid_argument("CSV rows must have the same number of columns");
        }

        dataset.target.push_back(values[0]);
        dataset.features.emplace_back(values.begin() + 1, values.end());
    }

    if (dataset.features.empty()) {
        throw std::invalid_argument("CSV file has no data rows");
    }
    return dataset;
}

} // namespace lasso
