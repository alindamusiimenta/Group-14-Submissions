#include "lasso/week3.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

int main() {
    const lasso::Dataset data = lasso::load_csv("data/input/sample.csv");
    assert(data.features.size() == 8);
    assert(data.features[0].size() == 3);
    assert(lasso::all_finite(data.features, data.target));

    const lasso::TrainTestSplit split = lasso::split_dataset(data, 0.75, 42);
    assert(split.train.target.size() == 6);
    assert(split.test.target.size() == 2);
    const lasso::TrainTestSplit repeated_split = lasso::split_dataset(data, 0.75, 42);
    assert(split.train.target == repeated_split.train.target);

    const lasso::FittedScaler scaler = lasso::fit_scaler(split.train.features);
    const lasso::Matrix scaled_test = scaler.transform(split.test.features);
    assert(scaled_test.size() == split.test.features.size());

    const lasso::Vector prediction = lasso::predict_rows({{1, 2}}, {2, 3});
    assert(std::abs(prediction[0] - 8.0) < 1e-12);
    const lasso::Vector prediction_with_intercept = lasso::predict_rows({{1, 2}}, {2, 3}, 4.0);
    assert(std::abs(prediction_with_intercept[0] - 12.0) < 1e-12);

    const std::vector<std::size_t> selected =
        lasso::selected_features({2.0, 0.00000001, -1.0});
    assert(selected.size() == 2);

    const lasso::RegressionMetrics metrics = lasso::evaluate_regression({1, 2, 3}, {2, 2, 4});
    assert(std::abs(metrics.mae - (2.0 / 3.0)) < 1e-12);
    assert(std::abs(metrics.rmse - std::sqrt(2.0 / 3.0)) < 1e-12);

    bool rejected_bad_threshold = false;
    try {
        (void)lasso::selected_features({1.0}, -0.1);
    } catch (const std::invalid_argument&) {
        rejected_bad_threshold = true;
    }
    assert(rejected_bad_threshold);

    bool rejected_bad_fraction = false;
    try {
        (void)lasso::split_dataset(data, 1.0, 42);
    } catch (const std::invalid_argument&) {
        rejected_bad_fraction = true;
    }
    assert(rejected_bad_fraction);

    const lasso::Vector not_finite{std::numeric_limits<double>::quiet_NaN()};
    assert(!lasso::all_finite({not_finite}, {1.0}));

    std::cout << "All LASSO Week 3 tests passed.\n";
}
