#include "lasso/week3.hpp"
#include <cmath>
#include <stdexcept>

namespace lasso {

ScaledData standardize(const Matrix& features) {
    if (features.empty() || features[0].empty()) throw std::invalid_argument("features cannot be empty");
    const std::size_t rows = features.size();
    const std::size_t columns = features[0].size();
    ScaledData result;
    result.features = features;
    result.means.assign(columns, 0.0);
    result.standard_deviations.assign(columns, 0.0);

    for (const Vector& row : features) if (row.size() != columns) throw std::invalid_argument("rows must have equal sizes");
    for (std::size_t column = 0; column < columns; ++column) {
        for (const Vector& row : features) result.means[column] += row[column];
        result.means[column] /= static_cast<double>(rows);
        for (const Vector& row : features) {
            const double difference = row[column] - result.means[column];
            result.standard_deviations[column] += difference * difference;
        }
        result.standard_deviations[column] = std::sqrt(result.standard_deviations[column] / rows);
        if (result.standard_deviations[column] == 0.0) result.standard_deviations[column] = 1.0;
    }
    for (Vector& row : result.features) for (std::size_t column = 0; column < columns; ++column)
        row[column] = (row[column] - result.means[column]) / result.standard_deviations[column];
    return result;
}

} // namespace lasso

// Week 3 continuation: fit the scaler on training data and reuse it on test data.
#include <stdexcept>
namespace lasso {
FittedScaler fit_scaler(const Matrix& training_features) {
    if (training_features.empty() || training_features[0].empty()) throw std::invalid_argument("training features cannot be empty");
    const std::size_t rows = training_features.size();
    const std::size_t columns = training_features[0].size();
    FittedScaler scaler;
    scaler.means.assign(columns, 0.0);
    scaler.standard_deviations.assign(columns, 0.0);
    for (const Vector& row : training_features) {
        if (row.size() != columns) throw std::invalid_argument("feature rows must have equal sizes");
        for (std::size_t column = 0; column < columns; ++column) scaler.means[column] += row[column];
    }
    for (double& mean : scaler.means) mean /= static_cast<double>(rows);
    for (const Vector& row : training_features) for (std::size_t column = 0; column < columns; ++column) {
        const double difference = row[column] - scaler.means[column];
        scaler.standard_deviations[column] += difference * difference;
    }
    for (double& deviation : scaler.standard_deviations) {
        deviation = std::sqrt(deviation / static_cast<double>(rows));
        if (deviation == 0.0) deviation = 1.0;
    }
    return scaler;
}
Matrix FittedScaler::transform(const Matrix& features) const {
    Matrix result = features;
    for (Vector& row : result) {
        if (row.size() != means.size()) throw std::invalid_argument("feature width does not match scaler");
        for (std::size_t column = 0; column < row.size(); ++column) row[column] = (row[column] - means[column]) / standard_deviations[column];
    }
    return result;
}
} // namespace lasso
