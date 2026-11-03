#pragma once

#include "lasso/week2.hpp"
#include <cstddef>
#include <vector>

namespace lasso {

struct TrainTestSplit {
    Dataset train;
    Dataset test;
};

// Randomly split rows with a repeatable seed.
TrainTestSplit split_dataset(const Dataset& data, double train_fraction, unsigned seed = 42);

struct FittedScaler {
    Vector means;
    Vector standard_deviations;
    // Apply saved training means and deviations to new rows.
    Matrix transform(const Matrix& features) const;
};

// Learn scaling values from training rows only.
FittedScaler fit_scaler(const Matrix& training_features);

// Return false if dimensions or values are invalid or non-finite.
bool all_finite(const Matrix& features, const Vector& target);

// Predict each row using the supplied coefficient vector and intercept.
Vector predict_rows(const Matrix& features, const Vector& coefficients, double intercept = 0.0);

// Return indexes of coefficients whose absolute values exceed the threshold.
std::vector<std::size_t> selected_features(const Vector& coefficients, double threshold = 0.000001);

struct RegressionMetrics {
    double mae;
    double mse;
    double rmse;
    double r_squared;
};

RegressionMetrics evaluate_regression(const Vector& actual, const Vector& predicted);

// Week 3 demonstration helper: choose the candidate with the lowest training cost.
// Use the cross-validation selector in week4.hpp for model selection.
double choose_lambda(const Matrix& features, const Vector& target,
                     const Vector& candidates);

} // namespace lasso
