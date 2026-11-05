#include "lasso/week3.hpp"

#include <cmath>
#include <stdexcept>

namespace lasso {

ScaledData standardize(const Matrix& features) {
    Vector unused_targets(features.size(), 0.0);
    check_preprocessing_input(features, unused_targets);

    const FittedScaler scaler = fit_scaler(features);
    return {scaler.transform(features), scaler.means, scaler.standard_deviations};
}

FittedScaler fit_scaler(const Matrix& training_features) {
    Vector unused_targets(training_features.size(), 0.0);
    check_preprocessing_input(training_features, unused_targets);

    const std::size_t row_count = training_features.size();
    const std::size_t column_count = training_features[0].size();

    FittedScaler scaler;
    scaler.means.assign(column_count, 0.0);
    scaler.standard_deviations.assign(column_count, 0.0);

    for (const Vector& row : training_features) {
        for (std::size_t column = 0; column < column_count; ++column) {
            scaler.means[column] += row[column];
        }
    }
    for (double& mean : scaler.means) {
        mean /= static_cast<double>(row_count);
    }

    for (const Vector& row : training_features) {
        for (std::size_t column = 0; column < column_count; ++column) {
            const double difference = row[column] - scaler.means[column];
            scaler.standard_deviations[column] += difference * difference;
        }
    }
    for (double& deviation : scaler.standard_deviations) {
        deviation = std::sqrt(deviation / static_cast<double>(row_count));
        if (deviation == 0.0) {
            deviation = 1.0;
        }
    }

    return scaler;
}

Matrix FittedScaler::transform(const Matrix& features) const {
    if (means.empty() || means.size() != standard_deviations.size()) {
        throw std::invalid_argument("scaler must have matching means and deviations");
    }

    Matrix transformed = features;
    for (Vector& row : transformed) {
        if (row.size() != means.size()) {
            throw std::invalid_argument("feature width does not match scaler");
        }
        for (std::size_t column = 0; column < row.size(); ++column) {
            if (!std::isfinite(row[column])) {
                throw std::invalid_argument("feature values must be finite");
            }
            row[column] = (row[column] - means[column]) / standard_deviations[column];
        }
    }
    return transformed;
}

} // namespace lasso
