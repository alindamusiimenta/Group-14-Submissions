#include "lasso/week3.hpp"   // Declares Matrix, Vector, ScaledData, FittedScaler
#include <cmath>             // std::sqrt
#include <stdexcept>         // std::invalid_argument

namespace lasso {

// standardize: z-score scaling of every column in one step.
//
// For each column j, every value x becomes (x - mean_j) / std_j, so each
// column ends up with mean 0 and standard deviation 1. Lasso penalizes the
// size of coefficients, so features on larger scales would otherwise be
// penalized unfairly. Standardizing puts all features on equal footing.
//
// Returns a ScaledData holding the scaled matrix plus the means and standard
// deviations that were used (handy for undoing or reusing the scaling).

ScaledData standardize(const Matrix& features) {
    // Reject empty input (no rows, or a first row with no columns).
    if (features.empty() || features[0].empty()) throw std::invalid_argument("features cannot be empty");

    const std::size_t rows = features.size();         // number of samples (n)
    const std::size_t columns = features[0].size();   // number of features (p)

    ScaledData result;
    result.features = features;                       // copy; scaled in place at the end
    result.means.assign(columns, 0.0);                // one mean per column, starts at 0
    result.standard_deviations.assign(columns, 0.0);  // accumulates sum of squares, then becomes std

    // Validate that the matrix is rectangular (every row has the same width).
    for (const Vector& row : features) if (row.size() != columns) throw std::invalid_argument("rows must have equal sizes");

    // Process one column at a time to compute its statistics.
    for (std::size_t column = 0; column < columns; ++column) {
        // Pass 1: sum the column, then divide by n to get the mean.
        for (const Vector& row : features) result.means[column] += row[column];
        result.means[column] /= static_cast<double>(rows);

        // Pass 2: accumulate squared deviations from the mean.
        for (const Vector& row : features) {
            const double difference = row[column] - result.means[column];
            result.standard_deviations[column] += difference * difference;
        }
        // Divide by n (population std, not n-1 sample std), then take sqrt.
        result.standard_deviations[column] = std::sqrt(result.standard_deviations[column] / rows);

        // A constant column has std 0, which would cause division by zero.
        // Setting std to 1 leaves such a column as all zeros after centering.
        if (result.standard_deviations[column] == 0.0) result.standard_deviations[column] = 1.0;
    }

    // Apply the transformation to the copied matrix: (x - mean) / std.
    for (Vector& row : result.features) for (std::size_t column = 0; column < columns; ++column)
        row[column] = (row[column] - result.means[column]) / result.standard_deviations[column];

    return result;
}

} // namespace lasso

// Week 3 continuation: fit the scaler on training data and reuse it on test data.
// Why split fitting from transforming?
// The test set must be scaled using the TRAINING set's mean and std. Computing
// statistics from test data would leak information from the test set into the
// model evaluation and make results look better than they really are.
#include <stdexcept>
namespace lasso {

// fit_scaler: learns per-column means and standard deviations from the
// training data only. It does not modify the data; it returns a FittedScaler
// that can later be applied to any matrix with the same number of columns.
FittedScaler fit_scaler(const Matrix& training_features) {
    if (training_features.empty() || training_features[0].empty()) throw std::invalid_argument("training features cannot be empty");

    const std::size_t rows = training_features.size();        // n samples
    const std::size_t columns = training_features[0].size();  // p features

    FittedScaler scaler;
    scaler.means.assign(columns, 0.0);
    scaler.standard_deviations.assign(columns, 0.0);

    // Single pass over rows: check each row's width and add its values into
    // the per-column running sums (these become means after the division below).
    for (const Vector& row : training_features) {
        if (row.size() != columns) throw std::invalid_argument("feature rows must have equal sizes");
        for (std::size_t column = 0; column < columns; ++column) scaler.means[column] += row[column];
    }
    // Convert the sums into means.
    for (double& mean : scaler.means) mean /= static_cast<double>(rows);

    // Accumulate squared deviations from each column's mean.
    for (const Vector& row : training_features) for (std::size_t column = 0; column < columns; ++column) {
        const double difference = row[column] - scaler.means[column];
        scaler.standard_deviations[column] += difference * difference;
    }
    // Turn the sums of squares into population standard deviations.
    for (double& deviation : scaler.standard_deviations) {
        deviation = std::sqrt(deviation / static_cast<double>(rows));
        // Guard against division by zero for constant columns.
        if (deviation == 0.0) deviation = 1.0;
    }
    return scaler;
}

// FittedScaler::transform: applies the stored training statistics to any
// matrix (training, validation, or test). Returns a new scaled matrix and
// leaves the input untouched.
Matrix FittedScaler::transform(const Matrix& features) const {
    Matrix result = features;   // work on a copy
    for (Vector& row : result) {
        // The new data must have the same number of features the scaler was fit on.
        if (row.size() != means.size()) throw std::invalid_argument("feature width does not match scaler");
        // Apply (x - training_mean) / training_std to each value.
        for (std::size_t column = 0; column < row.size(); ++column) row[column] = (row[column] - means[column]) / standard_deviations[column];
    }
    return result;
}

} // namespace lasso