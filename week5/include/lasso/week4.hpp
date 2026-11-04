#pragma once

#include "lasso/week3.hpp"
#include <vector>

namespace lasso
{

    struct CrossValidationResult
    {
        double lambda;
        double mean_validation_rmse;
        std::vector<double> fold_rmse;
    };
    // Evaluate one lambda with deterministic k-fold cross-validation.
    // Every fold fits its scaler on that fold's training rows only.
    CrossValidationResult cross_validate_lambda(const Dataset &data, double lambda,
                                                int folds = 5, unsigned seed = 42);

    // Return the lambda with the lowest mean validation RMSE.
    CrossValidationResult select_lambda_by_cross_validation(const Dataset &data,
                                                            const Vector &candidates,
                                                            int folds = 5,
                                                            unsigned seed = 42);

}
