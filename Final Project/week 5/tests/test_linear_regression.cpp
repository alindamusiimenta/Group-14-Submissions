
// Tests for Member 05's one-feature linear-regression implementation.
// These tests check whether the model produces correct results
// and handles invalid inputs properly.

#include "linreg/linear_regression.hpp"

#include <cassert>     // Provides assert() to check expected results.
#include <cmath>       // Provides std::abs() for comparing decimal values.
#include <iostream>    // Allows us to display the test results.
#include <stdexcept>   // Provides exception types used in error handling.
#include <vector>      // Allows us to create datasets using vectors.

int main() {

    // ---------------------------------------------------------
    // 1. CREATE A TEST DATASET
    // ---------------------------------------------------------

    // This dataset follows the equation y = 1 + 2x.
    // We already know the correct answer:
    // Intercept = 1 and slope = 2.
    // This makes it easy to check whether our model works correctly.
    const std::vector<double> x{1, 2, 3, 4};
    const std::vector<double> y{3, 5, 7, 9};

    // Create an object of the LinearRegression class.
    // We will use this object to train and test the model.
    linreg::LinearRegression model;


    // ---------------------------------------------------------
    // 2. TEST PREDICTION BEFORE TRAINING
    // ---------------------------------------------------------

    // The model should not make predictions before it has been trained.
    // We try to predict a value and check whether an exception is raised.
    bool rejected_prediction_before_fit = false;

    try {
        (void)model.predict(5.0);
    } catch (const std::logic_error&) {

        // If the exception is caught, the model correctly rejected
        // the prediction because training had not yet been performed.
        rejected_prediction_before_fit = true;
    }

    // Confirm that prediction before training was rejected.
    assert(rejected_prediction_before_fit);


    // ---------------------------------------------------------
    // 3. TEST CLOSED-FORM LEAST-SQUARES METHOD
    // ---------------------------------------------------------

    // Train the model using the closed-form method.
    // This method calculates the best-fit intercept and slope directly.
    const linreg::FitResult closed = model.fit_closed_form(x, y);

    // Check whether the calculated intercept is approximately 1.
    assert(std::abs(closed.intercept - 1.0) < 1e-10);

    // Check whether the calculated slope is approximately 2.
    assert(std::abs(closed.slope - 2.0) < 1e-10);

    // Check whether R-squared is approximately 1.
    // A value of 1 indicates a perfect fit for this dataset.
    assert(std::abs(closed.r_squared - 1.0) < 1e-10);


    // ---------------------------------------------------------
    // 4. TEST BATCH GRADIENT DESCENT
    // ---------------------------------------------------------

    // Train the model using batch gradient descent.
    // Learning rate = 0.01 and number of iterations = 3000.
    // The method should gradually approach the correct parameters.
    const linreg::FitResult gradient =
        model.fit_gradient_descent(x, y, 0.01, 3000);

    // Check whether the calculated slope is close to the expected value of 2.
    // A small tolerance is allowed because gradient descent is iterative.
    assert(std::abs(gradient.slope - 2.0) < 1e-3);

    // For x = 5, the expected prediction is:
    // y = 1 + 2(5) = 11.
    assert(std::abs(model.predict(5.0) - 11.0) < 1e-2);

    // Check whether the correlation coefficient is approximately 1.
    // This indicates a perfect positive linear relationship.
    assert(std::abs(linreg::correlation_coefficient(x, y) - 1.0) < 1e-10);


    // ---------------------------------------------------------
    // 5. TEST STOCHASTIC GRADIENT DESCENT
    // ---------------------------------------------------------

    // Train the model using stochastic gradient descent.
    // Unlike batch gradient descent, it updates the parameters
    // using one observation at a time.
    // The seed of 7 makes the random sequence reproducible.
    const linreg::FitResult stochastic =
        model.fit_stochastic_gradient_descent(x, y, 0.001, 3000, 7);

    // Check whether the resulting slope is close to the expected value of 2.
    assert(std::abs(stochastic.slope - 2.0) < 1e-2);


    // ---------------------------------------------------------
    // 6. TEST TRAINING AND TESTING DATA SPLITTING
    // ---------------------------------------------------------

    // Create a larger dataset containing 10 observations.
    const std::vector<double> larger_x{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const std::vector<double> larger_y{2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

    // Split the dataset using a test fraction of 0.2 (20%).
    // shuffle = false means the original order is maintained.
    const linreg::DatasetSplit split =
        linreg::train_test_split(larger_x, larger_y, 0.2, 42, false);

    // Check that 2 observations were reserved for testing.
    assert(split.test_x.size() == 2);

    // Check that the remaining 8 observations are used for training.
    assert(split.train_x.size() == 8);

    // Since shuffling is disabled, the first observation goes to testing.
    assert(split.test_x.front() == 1.0);

    // Check that the last training target is 20.
    assert(split.train_y.back() == 20.0);


    // ---------------------------------------------------------
    // 7. TEST REPRODUCIBILITY OF RANDOM SPLITTING
    // ---------------------------------------------------------

    // Split the same dataset twice using the same random seed.
    // Both operations should produce the same test subset.
    const linreg::DatasetSplit repeated_a =
        linreg::train_test_split(larger_x, larger_y, 0.2, 42, true);

    const linreg::DatasetSplit repeated_b =
        linreg::train_test_split(larger_x, larger_y, 0.2, 42, true);

    // Check that both test subsets are identical.
    // This confirms that the random split is reproducible.
    assert(repeated_a.test_x == repeated_b.test_x);


    // ---------------------------------------------------------
    // 8. TEST INVALID TEST FRACTION
    // ---------------------------------------------------------

    // A test fraction of 1.0 is invalid because it would leave
    // no observations available for training.
    bool rejected_fraction = false;

    try {
        (void)linreg::train_test_split(larger_x, larger_y, 1.0);
    } catch (const std::invalid_argument&) {

        // The function correctly rejected the invalid fraction.
        rejected_fraction = true;
    }

    // Confirm that the invalid test fraction was rejected.
    assert(rejected_fraction);


    // ---------------------------------------------------------
    // 9. CHECK THAT AT LEAST ONE TRAINING OBSERVATION REMAINS
    // ---------------------------------------------------------

    // A test fraction of 0.99 reserves most of the data for testing.
    // However, the function should still leave at least one
    // observation for training.
    bool kept_training_row = false;

    const linreg::DatasetSplit small_training =
        linreg::train_test_split(larger_x, larger_y, 0.99, 42, false);

    // Check whether one training observation was retained.
    kept_training_row = small_training.train_x.size() == 1;

    assert(kept_training_row);


    // ---------------------------------------------------------
    // 10. TEST CONSTANT INPUT VALUES
    // ---------------------------------------------------------

    // A regression slope cannot be uniquely calculated when all
    // input values are identical.
    // Here, both x values are 1, so the function should reject
    // this dataset when using the closed-form method.
    bool rejected_constant_x = false;

    try {
        (void)model.fit_closed_form({1.0, 1.0}, {2.0, 3.0});
    } catch (const std::invalid_argument&) {

        // The model correctly rejects the constant input values.
        rejected_constant_x = true;
    }

    // Confirm that the invalid dataset was rejected.
    assert(rejected_constant_x);


    // ---------------------------------------------------------
    // 11. DISPLAY THE FINAL TEST RESULT
    // ---------------------------------------------------------

    // If the program reaches this statement, all assertions
    // above have passed successfully.
    std::cout << "All linear regression tests passed.\n";
}
