#include "lasso/week3.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

int main() {
    const lasso::Dataset data{{{1, 60}, {2, 65}, {3, 70}, {4, 80}, {5, 90}, {6, 92}, {7, 95}, {8, 96}},
                              {52, 55, 61, 66, 70, 74, 78, 81}};
    assert(lasso::all_finite(data.features, data.target));
    const auto split = lasso::split_dataset(data, 0.75, 42);
    assert(split.train.target.size() == 6);
    assert(split.test.target.size() == 2);
    const auto scaler = lasso::fit_scaler(split.train.features);
    const auto scaled = scaler.transform(split.test.features);
    assert(scaled.size() == split.test.features.size());
    const auto prediction = lasso::predict_rows({{1, 2}}, {2, 3});
    assert(std::abs(prediction[0] - 8.0) < 1e-12);
    const auto prediction_with_intercept = lasso::predict_rows({{1, 2}}, {2, 3}, 4.0);
    assert(std::abs(prediction_with_intercept[0] - 12.0) < 1e-12);
    assert(lasso::selected_features({2.0, 0.00000001, -1.0}).size() == 2);
    bool bad_threshold_rejected = false;
    try { (void)lasso::selected_features({1.0}, -0.1); }
    catch (const std::invalid_argument&) { bad_threshold_rejected = true; }
    assert(bad_threshold_rejected);
    bool bad_lambda_rejected = false;
    try { (void)lasso::choose_lambda({{1.0}}, {2.0}, {0.1, -0.2}); }
    catch (const std::invalid_argument&) { bad_lambda_rejected = true; }
    assert(bad_lambda_rejected);
    const auto metrics = lasso::evaluate_regression({1, 2, 3}, {2, 2, 4});
    assert(std::abs(metrics.mae - (2.0 / 3.0)) < 1e-12);
    assert(std::abs(metrics.rmse - std::sqrt(2.0 / 3.0)) < 1e-12);
    assert(lasso::choose_lambda(scaled, split.test.target, {0.01, 0.1}) >= 0.01);
    std::cout << "All LASSO Week 3 tests passed.\n";
}
