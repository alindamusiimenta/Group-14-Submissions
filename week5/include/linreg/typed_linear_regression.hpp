#pragma once

// This file allows linear regression to work with different
// numeric data types such as int, float and double.
// The values are converted to double before training.

#include "linreg/linear_regression.hpp"
#include "numerics/numeric_types.hpp"

#include <cstddef>
#include <vector>

namespace linreg {

// InputT represents the input data type.
// TargetT represents the target data type.
// TargetT uses InputT by default.
template <typename InputT, typename TargetT = InputT>
class TypedLinearRegression {
    // Check that both input and target types are numeric.
    // This prevents unsupported data types from being used.
    static_assert(numerics::is_numeric_v<InputT>, "input type must be numeric");
    static_assert(numerics::is_numeric_v<TargetT>, "target type must be numeric");

public:
    // Convert the input and target values to double,
    // then use the main model to calculate the best-fit line.
    FitResult fit_closed_form(const std::vector<InputT>& x,
                              const std::vector<TargetT>& y) {
        return model_.fit_closed_form(numerics::to_double_vector(x),
                                      numerics::to_double_vector(y));
    }

    // Train the model using batch gradient descent.
    // The learning rate controls the size of each update,
    // while iterations controls the number of updates.
    FitResult fit_gradient_descent(const std::vector<InputT>& x,
                                   const std::vector<TargetT>& y,
                                   double learning_rate = 0.01,
                                   std::size_t iterations = 1000) {
        return model_.fit_gradient_descent(numerics::to_double_vector(x),
                                           numerics::to_double_vector(y),
                                           learning_rate, iterations);
    }

    // Train the model using stochastic gradient descent.
    // The model updates its parameters using individual observations.
    FitResult fit_stochastic_gradient_descent(const std::vector<InputT>& x,
                                              const std::vector<TargetT>& y,
                                              double learning_rate = 0.001,
                                              std::size_t epochs = 1000,
                                              unsigned seed = 42) {
        return model_.fit_stochastic_gradient_descent(
            numerics::to_double_vector(x), numerics::to_double_vector(y),
            learning_rate, epochs, seed);
    }

    // Accept a numeric input, convert it to double,
    // and use the trained model to calculate the prediction.
    template <typename PredictionT>
    double predict(PredictionT x) const {
        static_assert(numerics::is_numeric_v<PredictionT>, "prediction input must be numeric");
        return model_.predict(numerics::to_double(x));
    }

    // Return the intercept and slope learned during training.
    double intercept() const noexcept {
        return model_.intercept();
    }

    double slope() const noexcept {
        return model_.slope();
    }

private:
    // Store the main LinearRegression object.
    // It performs the actual regression calculations.
    LinearRegression model_;
};

} // namespace linreg
