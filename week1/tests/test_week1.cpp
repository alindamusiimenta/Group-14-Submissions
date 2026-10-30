#include "lasso/lasso_regression.hpp"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>

int main() {
    assert(std::abs(lasso::dot({1, 2, 3}, {4, 5, 6}) - 32.0) < 1e-12);
    const auto product = lasso::matrix_vector_product({{1, 2}, {3, 4}}, {2, 1});
    assert(product.size() == 2 && product[0] == 4.0 && product[1] == 10.0);
    assert(lasso::soft_threshold(5.0, 2.0) == 3.0);
    assert(lasso::soft_threshold(-5.0, 2.0) == -3.0);
    assert(lasso::soft_threshold(1.0, 2.0) == 0.0);

    const lasso::Matrix features{{1, 2}, {2, 1}};
    const lasso::Vector target{5, 4};
    const lasso::Vector coefficients{1, 2};
    assert(std::abs(lasso::lasso_cost(features, target, coefficients, 0.5) - 1.5) < 1e-12);

    const auto baseline = lasso::linear_regression_baseline({1, 2, 3, 4}, {3, 5, 7, 9});
    assert(std::abs(baseline.intercept - 1.0) < 1e-12);
    assert(std::abs(baseline.slope - 2.0) < 1e-12);
    assert(baseline.mse < 1e-12);

    lasso::LassoModel model;
    model.fit_baseline({1, 2, 3}, {3, 5, 7});
    assert(std::abs(model.predict(4.0) - 9.0) < 1e-12);

    bool rejected = false;
    try { lasso::dot({1}, {1, 2}); }
    catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);

    // Member 1: loader reads target first, then features.
    {
        std::ofstream out("member01_test.csv");
        out << "target,a,b\n5,1,2\n4,2,1\n";
    }
    const lasso::Dataset loaded = lasso::load_csv("member01_test.csv");
    assert(loaded.target.size() == 2 && loaded.target[0] == 5.0);
    assert(loaded.features[1].size() == 2 && loaded.features[1][0] == 2.0);
    std::remove("member01_test.csv");

    // Member 2: shape checks.
    assert(lasso::rows_match_target({{1, 2}, {3, 4}}, {5, 6}));
    assert(!lasso::rows_match_target({{1, 2}}, {5, 6}));
    assert(lasso::rows_have_equal_width({{1, 2}, {3, 4}}));
    assert(!lasso::rows_have_equal_width({{1, 2}, {3}}));

    // Member 3: statistics of one column.
    assert(std::abs(lasso::mean({1, 2, 3}) - 2.0) < 1e-12);
    assert(std::abs(lasso::standard_deviation({2, 4, 4, 4, 5, 5, 7, 9}) - 2.0) < 1e-12);

    // Member 8: one coefficient update.
    assert(lasso::update_coefficient(5.0, 1.0, 2.0) == 3.0);
    assert(lasso::update_coefficient(1.0, 1.0, 2.0) == 0.0);
    assert(std::abs(lasso::update_coefficient(5.0, 2.0, 1.0) - 2.0) < 1e-12);

    // Member 9: mean squared error.
    assert(std::abs(lasso::mean_squared_error({1, 2, 3}, {2, 2, 4}) - 2.0 / 3.0) < 1e-12);

    bool bad_mean = false;
    try { lasso::mean({}); }
    catch (const std::invalid_argument&) { bad_mean = true; }
    assert(bad_mean);

    std::cout << "All LASSO Week 1 tests passed.\n";
}
