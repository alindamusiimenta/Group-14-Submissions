#include "lasso/week3.hpp"

#include <cmath>
#include <limits>
#include <stdexcept>

namespace lasso {

double choose_lambda(const Matrix& features,
                     const Vector& target,
                     const Vector& candidates) {

    // Validate the input data before attempting model fitting.
    check_preprocessing_input(features, target);

    // At least one candidate is required.
    if (candidates.empty()) {
        throw std::invalid_argument(
            "at least one lambda candidate is required");
    }

    // Ensure all regularization strengths are valid.
    for (double lambda : candidates) {
        if (lambda < 0.0 || !std::isfinite(lambda)) {
            throw std::invalid_argument(
                "lambda candidates must be non-negative and finite");
        }
    }

    // Track the candidate with the lowest cost.
    double best_lambda = candidates[0];
    double best_cost = std::numeric_limits<double>::infinity();

    // Fit the model using each candidate.
    for (double lambda : candidates) {

        const LassoFit fit =
            coordinate_descent(features, target, lambda, 500);

        if (fit.cost < best_cost) {
            best_cost = fit.cost;
            best_lambda = lambda;
        }
    }

    return best_lambda;
}

} // namespace lasso