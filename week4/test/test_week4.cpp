#include "lasso/week4.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

int main() {
    const lasso::Dataset data{
        {{1, 2}, {2, 1}, {3, 4}, {4, 3}, {5, 6}, {6, 5}, {7, 8}, {8, 7}},
        {2.1, 2.8, 4.2, 4.8, 6.1, 6.9, 8.2, 8.8}
    };

    const lasso::CrossValidationResult first = lasso::cross_validate_lambda(data, 0.01, 4, 42);
    const lasso::CrossValidationResult repeated = lasso::cross_validate_lambda(data, 0.01, 4, 42);
    assert(first.fold_rmse.size() == 4);
    assert(std::isfinite(first.mean_validation_rmse));
    assert(std::abs(first.mean_validation_rmse - repeated.mean_validation_rmse) < 1e-12);

    const lasso::CrossValidationResult best =
        lasso::select_lambda_by_cross_validation(data, {0.001, 0.01, 0.1}, 4, 42);
    assert(best.lambda >= 0.0);
    assert(std::isfinite(best.mean_validation_rmse));

    bool rejected_bad_fold_count = false;
    try {
        (void)lasso::cross_validate_lambda(data, 0.1, 1, 42);
    } catch (const std::invalid_argument&) {
        rejected_bad_fold_count = true;
    }
    assert(rejected_bad_fold_count);

    bool rejected_negative_lambda = false;
    try {
        (void)lasso::cross_validate_lambda(data, -0.1, 4, 42);
    } catch (const std::invalid_argument&) {
        rejected_negative_lambda = true;
    }
    assert(rejected_negative_lambda);

    std::cout << "All LASSO Week 4 tests passed.\n";
}
