#include "lasso/week3.hpp" // group header file

#include <cmath>    //to include the std:: isfinite
#include <limits>    // to include numeric limits libraries
#include <stdexcept>  // for error reporting

namespace lasso {    // allows keeping the group's code in one namesace

// function that allows candidate values of lambda
double choose_lambda(const Matrix& features, const Vector& target, const Vector& candidates) {
// Validate the data before attempting any model fits.
check_preprocessing_input(features, target);
    
if (candidates.empty()) {//throws an error incase no data is input
throw std::invalid_argument("at least one lambda candidate is required");
}

// Reject invalid regularization strengths(lambda) before evaluating the candidates.  
for (double lambda : candidates) {  //check every candidate first
if (lambda < 0.0 || !std::isfinite(lambda)) { // if negative, not a number or infinite
throw std::invalid_argument("lambda candidates must be non-negative and finite"); //throw this error message
}
    }
double best_lambda = candidates[0]; // starting with the first candidate
double best_cost = std::numeric_limits<double>::infinity(); // any real cost will better than infinity

// Fit each candidate (lambda) and retain the one with the lowest cost.
for (double lambda : candidates) {
const LassoFit fit = coordinate_descent(features, target, lambda, 500);
        
if (fit.cost < best_cost) { //  if lower keep the earlier candidate
best_cost = fit.cost;      // allows remembering the best cost so far
best_lambda = lambda;   // and the lambda that produced it
}
}
return best_lambda;    //best lambda
}

} // namespace lasso
