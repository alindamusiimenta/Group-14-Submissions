#include "linreg/linear_regression.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    const std::vector<double> x{1, 2, 3, 4};
    const std::vector<double> y{3, 5, 7, 9};
    linreg::LinearRegression model;

    bool rejected_prediction_before_fit = false;
    try {
        (void)model.predict(5.0);
    } catch (const std::logic_error&) {
        rejected_prediction_before_fit = true;
    }
    assert(rejected_prediction_before_fit);

    const linreg::FitResult closed = model.fit_closed_form(x, y);
    assert(std::abs(closed.intercept - 1.0) < 1e-10);
    assert(std::abs(closed.slope - 2.0) < 1e-10);
    assert(std::abs(closed.r_squared - 1.0) < 1e-10);

    const linreg::FitResult gradient = model.fit_gradient_descent(x, y, 0.01, 3000);
    assert(std::abs(gradient.slope - 2.0) < 1e-3);
    assert(std::abs(model.predict(5.0) - 11.0) < 1e-2);
    assert(std::abs(linreg::correlation_coefficient(x, y) - 1.0) < 1e-10);

    const linreg::FitResult stochastic =
        model.fit_stochastic_gradient_descent(x, y, 0.001, 3000, 7);
    assert(std::abs(stochastic.slope - 2.0) < 1e-2);

    const std::vector<double> larger_x{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const std::vector<double> larger_y{2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    const linreg::DatasetSplit split =
        linreg::train_test_split(larger_x, larger_y, 0.2, 42, false);
    assert(split.test_x.size() == 2);
    assert(split.train_x.size() == 8);
    assert(split.test_x.front() == 1.0);
    assert(split.train_y.back() == 20.0);

    const linreg::DatasetSplit repeated_a =
        linreg::train_test_split(larger_x, larger_y, 0.2, 42, true);
    const linreg::DatasetSplit repeated_b =
        linreg::train_test_split(larger_x, larger_y, 0.2, 42, true);
    assert(repeated_a.test_x == repeated_b.test_x);

    bool rejected_fraction = false;
    try {
        (void)linreg::train_test_split(larger_x, larger_y, 1.0);
    } catch (const std::invalid_argument&) {
        rejected_fraction = true;
    }
    assert(rejected_fraction);

    bool kept_training_row = false;
    const linreg::DatasetSplit small_training =
        linreg::train_test_split(larger_x, larger_y, 0.99, 42, false);
    kept_training_row = small_training.train_x.size() == 1;
    assert(kept_training_row);

    bool rejected_constant_x = false;
    try {
        (void)model.fit_closed_form({1.0, 1.0}, {2.0, 3.0});
    } catch (const std::invalid_argument&) {
        rejected_constant_x = true;
    }
    assert(rejected_constant_x);

    std::cout << "All linear regression tests passed.\n";
}
