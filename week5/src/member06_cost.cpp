#include "lasso/week3.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace lasso {

double choose_lambda(const Matrix& features, const Vector& target, const Vector& candidates) {
// Validate the shared input assumptions before evaluating any lambda values.
check_preprocessing_input(features, target);

// The search space must contain at least one candidate to be meaningful.
if (candidates.empty()) {
    throw std::invalid_argument("at least one lambda candidate is required");
}

// Reject invalid regularization strengths before running the optimization loop.
for (double lambda : candidates) {
    if (lambda < 0.0 || !std::isfinite(lambda)) {
        throw std::invalid_argument("lambda candidates must be non-negative and finite");
    }
}

// Track the candidate with the lowest observed objective value.
double best_lambda = candidates[0];
double best_cost = std::numeric_limits<double>::infinity();
for (double lambda : candidates) {
    
// Run the coordinate-descent fit for each regularization strength.
    const LassoFit fit = coordinate_descent(features, target, lambda, 500);

if (fit.cost < best_cost) {
    best_cost = fit.cost;
best_lambda = lambda;
    }
}
return best_lambda;
}

} // namespace lasso
