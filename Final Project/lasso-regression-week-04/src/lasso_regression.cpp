#include "lasso/lasso_regression.hpp"

#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace lasso {
namespace {
void check_same_size(const Vector& first, const Vector& second) {
    if (first.size() != second.size()) {
        throw std::invalid_argument("vectors must have the same size");
    }
    if (first.size() < 2) {
        throw std::invalid_argument("at least two values are required");
    }
}

void check_matrix(const Matrix& matrix, const Vector& target) {
    if (matrix.empty() || matrix.size() != target.size()) {
        throw std::invalid_argument("matrix and target have incompatible sizes");
    }
    const std::size_t columns = matrix[0].size();
    if (columns == 0) {
        throw std::invalid_argument("matrix must have at least one column");
    }
    for (const Vector& row : matrix) {
        if (row.size() != columns) {
            throw std::invalid_argument("all matrix rows must have the same size");
        }
    }
}
}

// Calculate a dot product with a simple loop.
double dot(const Vector& left, const Vector& right) {
    if (left.size() != right.size()) {
        throw std::invalid_argument("dot-product vectors must have the same size");
    }
    double answer = 0.0;
    for (std::size_t i = 0; i < left.size(); ++i) {
        answer += left[i] * right[i];
    }
    return answer;
}

Vector matrix_vector_product(const Matrix& matrix, const Vector& vector) {
    Vector result;
    for (const Vector& row : matrix) {
        result.push_back(dot(row, vector));
    }
    return result;
}

double soft_threshold(double value, double threshold) {
    if (threshold < 0.0) {
        throw std::invalid_argument("threshold cannot be negative");
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
    check_matrix(features, target);
    if (coefficients.size() != features[0].size()) {
        throw std::invalid_argument("coefficient count must match feature count");
    }
    if (lambda < 0.0 || !std::isfinite(lambda)) {
        throw std::invalid_argument("lambda must be non-negative and finite");
    }

    double squared_error = 0.0;
    for (std::size_t i = 0; i < features.size(); ++i) {
        const double prediction = dot(features[i], coefficients);
        const double error = prediction - target[i];
        squared_error += error * error;
    }

    double penalty = 0.0;
    for (double coefficient : coefficients) {
        penalty += std::abs(coefficient);
    }
    return squared_error / (2.0 * features.size()) + lambda * penalty;
}

BaselineResult linear_regression_baseline(const Vector& x, const Vector& y) {
    check_same_size(x, y);
    double sum_x = 0.0;
    double sum_y = 0.0;
    for (std::size_t i = 0; i < x.size(); ++i) {
        sum_x += x[i];
        sum_y += y[i];
    }
    const double mean_x = sum_x / x.size();
    const double mean_y = sum_y / y.size();

    double numerator = 0.0;
    double denominator = 0.0;
    for (std::size_t i = 0; i < x.size(); ++i) {
        numerator += (x[i] - mean_x) * (y[i] - mean_y);
        denominator += (x[i] - mean_x) * (x[i] - mean_x);
    }
    if (denominator == 0.0) {
        throw std::invalid_argument("x values must not all be equal");
    }

    const double slope = numerator / denominator;
    const double intercept = mean_y - slope * mean_x;
    double total_error = 0.0;
    for (std::size_t i = 0; i < x.size(); ++i) {
        const double error = intercept + slope * x[i] - y[i];
        total_error += error * error;
    }
    return {intercept, slope, total_error / x.size()};
}

void LassoModel::fit_baseline(const Vector& x, const Vector& y) {
    const BaselineResult result = linear_regression_baseline(x, y);
    intercept_ = result.intercept;
    slope_ = result.slope;
    fitted_ = true;
}

double LassoModel::predict(double x) const {
    if (!fitted_) {
        throw std::logic_error("model must be fitted before prediction");
    }
    return intercept_ + slope_ * x;
}

double LassoModel::intercept() const { return intercept_; }
double LassoModel::slope() const { return slope_; }

Dataset load_csv(const std::string& path, bool has_header) {
    std::ifstream file(path);
    if (!file) {
        throw std::invalid_argument("could not open CSV file");
    }

    Dataset dataset;
    std::string line;
    if (has_header) {
        std::getline(file, line);
    }

    std::size_t expected_feature_count = 0;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream row(line);
        std::string cell;
        Vector values;
        while (std::getline(row, cell, ',')) {
            try {
                values.push_back(std::stod(cell));
            } catch (...) {
                throw std::invalid_argument("CSV cells must be numbers");
            }
        }
        if (values.size() < 2) {
            throw std::invalid_argument("each CSV row needs a target and feature");
        }
        if (expected_feature_count == 0) {
            expected_feature_count = values.size() - 1;
        }
        if (values.size() - 1 != expected_feature_count) {
            throw std::invalid_argument("CSV rows must have the same number of columns");
        }
        dataset.target.push_back(values[0]);
        Vector features(values.begin() + 1, values.end());
        dataset.features.push_back(features);
    }
    if (dataset.features.empty()) {
        throw std::invalid_argument("CSV file has no data rows");
    }
    return dataset;
}
} // namespace lasso
