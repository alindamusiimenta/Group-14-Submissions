#include "lasso/week3.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

int main() {
    // Load the Week 5 sample dataset.
    const lasso::Dataset data =
        lasso::load_csv("data/input/sample.csv");

    assert(data.features.size() == 8);
    assert(data.features[0].size() == 3);
    assert(lasso::all_finite(data.features, data.target));

    // Test dataset splitting.
    const lasso::TrainTestSplit split =
        lasso::split_dataset(data, 0.75, 42);

    assert(split.train.target.size() == 6);
    assert(split.test.target.size() == 2);

    // Verify that the same seed produces the same split.
    const lasso::TrainTestSplit repeated_split =
        lasso::split_dataset(data, 0.75, 42);

    assert(split.train.target == repeated_split.train.target);

    // Test feature scaling.
    const lasso::FittedScaler scaler =
        lasso::fit_scaler(split.train.features);

    const lasso::Matrix scaled_test =
        scaler.transform(split.test.features);

    assert(scaled_test.size() == split.test.features.size());

    // Test predictions without an intercept.
    const lasso::Vector prediction =
        lasso::predict_rows({{1, 2}}, {2, 3});

    assert(std::abs(prediction[0] - 8.0) < 1e-12);

    // Test predictions with an intercept.
    const lasso::Vector prediction_with_intercept =
        lasso::predict_rows({{1, 2}}, {2, 3}, 4.0);

    assert(std::abs(prediction_with_intercept[0] - 12.0) < 1e-12);

    // Test feature selection.
    const std::vector<std::size_t> selected =
        lasso::selected_features({2.0, 0.00000001, -1.0});

    assert(selected.size() == 2);

    // Test rejection of an invalid feature-selection threshold.
    bool rejected_bad_threshold = false;

    try {
        (void)lasso::selected_features({1.0}, -0.1);
    } catch (const std::invalid_argument&) {
        rejected_bad_threshold = true;
    }

    assert(rejected_bad_threshold);

    // Test rejection of invalid lambda candidates.
    bool rejected_bad_lambda = false;

    try {
        (void)lasso::choose_lambda(
            {{1.0}}, {2.0}, {0.1, -0.2});
    } catch (const std::invalid_argument&) {
        rejected_bad_lambda = true;
    }

    assert(rejected_bad_lambda);

    // Test regression evaluation metrics.
    const lasso::RegressionMetrics metrics =
        lasso::evaluate_regression({1, 2, 3}, {2, 2, 4});

    assert(std::abs(metrics.mae - (2.0 / 3.0)) < 1e-12);
    assert(std::abs(metrics.rmse - std::sqrt(2.0 / 3.0)) < 1e-12);

    // Test rejection of an invalid training fraction.
    bool rejected_bad_fraction = false;

    try {
        (void)lasso::split_dataset(data, 1.0, 42);
    } catch (const std::invalid_argument&) {
        rejected_bad_fraction = true;
    }

    assert(rejected_bad_fraction);

    // Test rejection of non-finite values.
    const lasso::Vector not_finite{
        std::numeric_limits<double>::quiet_NaN()
    };

    assert(!lasso::all_finite({not_finite}, {1.0}));

    // Test lambda selection using coordinate descent.
    const double best_lambda =
        lasso::choose_lambda(
            scaled_test, split.test.target, {0.01, 0.1});

    assert(best_lambda == 0.01 || best_lambda == 0.1);

    std::cout << "All LASSO Week 3 tests passed.\n";

    return 0;
}