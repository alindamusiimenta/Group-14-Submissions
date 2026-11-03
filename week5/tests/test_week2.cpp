#include "lasso/week2.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

int main() {
    const lasso::Matrix features{{1, 60}, {2, 65}, {3, 70}, {4, 80}, {5, 90}};
    const lasso::Vector target{52, 55, 61, 66, 70};

    lasso::check_preprocessing_input(features, target);
    const lasso::ScaledData scaled = lasso::standardize(features);
    assert(std::abs(scaled.means[0] - 3.0) < 1e-12);
    assert(std::abs(scaled.means[1] - 73.0) < 1e-12);

    const lasso::LassoFit fit = lasso::coordinate_descent(scaled.features, target, 0.10, 500);
    assert(fit.coefficients.size() == 2);
    assert(fit.passes > 0 && fit.passes <= 500);
    assert(std::isfinite(fit.cost));
    assert(lasso::soft_threshold(5.0, 2.0) == 3.0);
    assert(std::abs(lasso::lasso_cost({{1.0}, {2.0}}, {1.0, 2.0}, {1.0}, 0.5) - 0.5) < 1e-12);
    assert(lasso::mean_absolute_error({1, 2, 3}, {2, 2, 4}) > 0.0);

    bool rejected_bad_rows = false;
    try {
        (void)lasso::standardize({{1, 2}, {3}});
    } catch (const std::invalid_argument&) {
        rejected_bad_rows = true;
    }
    assert(rejected_bad_rows);

    bool rejected_bad_lambda = false;
    try {
        (void)lasso::coordinate_descent(features, target, -0.1);
    } catch (const std::invalid_argument&) {
        rejected_bad_lambda = true;
    }
    assert(rejected_bad_lambda);

    std::cout << "All LASSO Week 2 tests passed.\n";
}
