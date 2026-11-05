#include "lasso/week4.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <stdexcept>

namespace lasso {
namespace {

Dataset make_subset(const Dataset& data, const std::vector<std::size_t>& row_ids) {
    Dataset subset;
    for (std::size_t row_id : row_ids) {
        subset.features.push_back(data.features.at(row_id));
        subset.target.push_back(data.target.at(row_id));
    }
    return subset;
}

double calculate_rmse(const Vector& actual, const Vector& predicted) {
    if (actual.empty() || actual.size() != predicted.size()) {
        throw std::invalid_argument("RMSE vectors must have equal non-empty sizes");
    }

    double squared_error_total = 0.0;
    for (std::size_t index = 0; index < actual.size(); ++index) {
        const double error = actual[index] - predicted[index];
        squared_error_total += error * error;
    }
    return std::sqrt(squared_error_total / static_cast<double>(actual.size()));
}

} // namespace

CrossValidationResult cross_validate_lambda(const Dataset& data, double lambda,
                                             int folds, unsigned seed) {
    check_preprocessing_input(data.features, data.target);
    if (folds < 2 || static_cast<std::size_t>(folds) > data.target.size()) {
        throw std::invalid_argument("folds must be between two and the number of rows");
    }
    if (lambda < 0.0 || !std::isfinite(lambda)) {
        throw std::invalid_argument("lambda must be non-negative and finite");
    }

    const std::size_t row_count = data.target.size();
    std::vector<std::size_t> row_order(row_count);
    std::iota(row_order.begin(), row_order.end(), 0);

    std::mt19937 generator(seed);
    std::shuffle(row_order.begin(), row_order.end(), generator);

    std::vector<double> fold_scores;
    fold_scores.reserve(static_cast<std::size_t>(folds));

    for (int fold = 0; fold < folds; ++fold) {
        std::vector<std::size_t> training_rows;
        std::vector<std::size_t> validation_rows;

        for (std::size_t position = 0; position < row_count; ++position) {
            if (position % static_cast<std::size_t>(folds) == static_cast<std::size_t>(fold)) {
                validation_rows.push_back(row_order[position]);
            } else {
                training_rows.push_back(row_order[position]);
            }
        }

        const Dataset training = make_subset(data, training_rows);
        const Dataset validation = make_subset(data, validation_rows);

        // Learn scaling values from the training rows only to avoid leakage.
        const FittedScaler scaler = fit_scaler(training.features);
        const Matrix scaled_training = scaler.transform(training.features);
        const Matrix scaled_validation = scaler.transform(validation.features);
        const LassoFit fit = coordinate_descent(scaled_training, training.target, lambda);
        const Vector predictions = predict_rows(scaled_validation, fit.coefficients, fit.intercept);
        fold_scores.push_back(calculate_rmse(validation.target, predictions));
    }

    const double score_total = std::accumulate(fold_scores.begin(), fold_scores.end(), 0.0);
    const double mean_score = score_total / static_cast<double>(fold_scores.size());
    return {lambda, mean_score, fold_scores};
}

CrossValidationResult select_lambda_by_cross_validation(const Dataset& data,
                                                        const Vector& candidates,
                                                        int folds, unsigned seed) {
    if (candidates.empty()) {
        throw std::invalid_argument("provide at least one lambda candidate");
    }
    for (double lambda : candidates) {
        if (lambda < 0.0 || !std::isfinite(lambda)) {
            throw std::invalid_argument("lambda candidates must be non-negative and finite");
        }
    }

    CrossValidationResult best{candidates[0], INFINITY, {}};
    for (double lambda : candidates) {
        const CrossValidationResult result = cross_validate_lambda(data, lambda, folds, seed);
        if (result.mean_validation_rmse < best.mean_validation_rmse) {
            best = result;
        }
    }
    return best;
}

} // namespace lasso
