#include "lasso/week3.hpp"
#include <limits>
#include <cmath>
#include <stdexcept>

namespace lasso {

    // the function choose_lambda , it lives in the lasso namespace,and take three parameters:
double choose_lambda(const Matrix& features, const Vector& target, const Vector& candidates) {

    // requires atleast one candidate lambda value:
    if (candidates.empty()) throw std::invalid_argument("at least one lambda is required");

    // validate the candidate lambda values:
for (double lambda : candidates) {

 if (lambda < 0.0 || !std::isfinite(lambda)) {
  throw std::invalid_argument("lambda candidates must be non-negative and finite");
 }
    }

    // start with the first candidate and keep the lowest cost seen so far:
double best_lambda = candidates[0]; 
double best_cost = std::numeric_limits<double>::infinity();

   // evaluating each lambda value and keeping the one that minimizes the lasso cost function:
for (double lambda : candidates) {
const LassoFit fit = coordinate_descent(features, target, lambda, 500);

 if (fit.cost < best_cost) {
best_cost = fit.cost;
best_lambda = lambda;
}   
}  

// return the lambda value that resulted in the lowest cost:
return best_lambda;
}

} // namespace lasso