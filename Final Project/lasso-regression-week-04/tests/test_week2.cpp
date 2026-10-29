#include "lasso/week2.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

int main() {
    const lasso::Matrix features{{1, 60}, {2, 65}, {3, 70}, {4, 80}, {5, 90}};
    const lasso::Vector target{52, 55, 61, 66, 70};
    lasso::check_preprocessing_input(features, target);
    const auto scaled = lasso::standardize(features);
    assert(std::abs(scaled.means[0] - 3.0) < 1e-12);
    assert(std::abs(scaled.means[1] - 73.0) < 1e-12);
    const auto fit = lasso::coordinate_descent(scaled.features, target, 0.10, 500);
    assert(fit.coefficients.size() == 2);
    assert(std::isfinite(fit.cost));
    assert(lasso::mean_absolute_error({1, 2, 3}, {2, 2, 4}) > 0.0);

    bool rejected = false;
    try { lasso::standardize({{1, 2}, {3}}); }
    catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);
    std::cout << "All LASSO Week 2 tests passed.\n";
}
