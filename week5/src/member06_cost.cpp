#include "lasso/week3.hpp" // group header file

#include <cmath>  //for detecting NaN or infinity
#include <limits>  //for getting limits by introducing std:: numeric limits
#include <stdexcept> // for reporting error by including std:: invalid_argument

namespace lasso {   // ensuring the group's code is in one namespace 

//a function that returns lambda of lowest cost
double choose_lambda(const Matrix& features,
                     const Vector& target,
                     const Vector& candidates) {

    // Validate the input data before attempting model fitting. (done during member2's check)
    check_preprocessing_input(features, target);

    // At least one candidate is required.
    if (candidates.empty()) { //if no candidate 
        throw std::invalid_argument( //throw an error
            "at least one lambda candidate is required");
    }

    // Ensure all regularization strengths (lambda values) are valid.
    for (double lambda : candidates) {
        if (lambda < 0.0 || !std::isfinite(lambda)) { //if lambda is negative , NaN or infinite
            throw std::invalid_argument( //throw an error
                "lambda candidates must be non-negative and finite");
        }
    }

    // Track the candidate with the lowest cost.
    double best_lambda = candidates[0]; // starting from the first candidate
    double best_cost = std::numeric_limits<double>::infinity(); //any positive cost is better than infinity  

    // Fit the model using each candidate.
    for (double lambda : candidates) {

    //training LASSO for each Lambda //done by member 8 giving at most 500passes 
        const LassoFit fit =
            coordinate_descent(features, target, lambda, 500);

        if (fit.cost < best_cost) { //for a lower fit ,keep the previous value
            best_cost = fit.cost; // keep the best cost so far
            best_lambda = lambda; // keep the lambda that produced the best cost
        }
    }

    return best_lambda;
}

} // namespace lasso
