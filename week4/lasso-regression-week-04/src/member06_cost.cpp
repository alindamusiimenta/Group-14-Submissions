#include "lasso/week3.hpp"
#include <limits>
#include <cmath>
#include <stdexcept>

namespace lasso {

double choose_lambda(const Matrix& features, const Vector& target, const Vector& candidates) {
    if (candidates.empty()) throw std::invalid_argument("at least one lambda is required");
    for (double lambda : candidates) {
        if (lambda < 0.0 || !std::isfinite(lambda)) {
            throw std::invalid_argument("lambda candidates must be non-negative and finite");
        }
    }
    double best_lambda = candidates[0];
    double best_cost = std::numeric_limits<double>::infinity();
    for (double lambda : candidates) {
        const LassoFit fit = coordinate_descent(features, target, lambda, 500);
        if (fit.cost < best_cost) {
            best_cost = fit.cost;
            best_lambda = lambda;
        }
    }
    return best_lambda;
}

} // namespace lasso
