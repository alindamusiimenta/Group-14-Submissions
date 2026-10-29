#pragma once

#include "lasso/week2.hpp"
#include <cstddef>
#include <vector>

namespace lasso {

struct TrainTestSplit {
    Dataset train;
    Dataset test;
};

TrainTestSplit split_dataset(const Dataset& data, double train_fraction, unsigned seed = 42);

struct FittedScaler {
    Vector means;
    Vector standard_deviations;
    Matrix transform(const Matrix& features) const;
};

FittedScaler fit_scaler(const Matrix& training_features);
bool all_finite(const Matrix& features, const Vector& target);
Vector predict_rows(const Matrix& features, const Vector& coefficients, double intercept = 0.0);
std::vector<std::size_t> selected_features(const Vector& coefficients, double threshold = 0.000001);

struct RegressionMetrics {
    double mae;
    double mse;
    double rmse;
    double r_squared;
};

RegressionMetrics evaluate_regression(const Vector& actual, const Vector& predicted);
double choose_lambda(const Matrix& features, const Vector& target,
                     const Vector& candidates);

} // namespace lasso
