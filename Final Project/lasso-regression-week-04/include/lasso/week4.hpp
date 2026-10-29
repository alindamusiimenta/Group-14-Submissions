#pragma once
#include "lasso/week3.hpp"
#include <vector>

namespace lasso {
struct CrossValidationResult {
    double lambda;
    double mean_validation_rmse;
    std::vector<double> fold_rmse;
};
// Deterministic k-fold CV. Each fold fits its scaler on training rows only.
CrossValidationResult cross_validate_lambda(const Dataset& data, double lambda,
                                            int folds = 5, unsigned seed = 42);
CrossValidationResult select_lambda_by_cross_validation(const Dataset& data,
                                            const Vector& candidates,
                                            int folds = 5, unsigned seed = 42);
} // namespace lasso
