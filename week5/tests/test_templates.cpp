#include "lasso/typed_lasso_regression.hpp"
#include "linreg/typed_linear_regression.hpp"
#include "numerics/csv_data_processor.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

int main() {
    const numerics::Matrix<short> matrix{{1, 2}, {3, 4}};
    const std::vector<float> weights{0.5F, 1.5F};
    const std::vector<double> product = matrix.multiply(weights);
    assert(product.size() == 2);
    assert(std::abs(product[0] - 3.5) < 1e-12);
    assert(std::abs(product[1] - 7.5) < 1e-12);
    assert(matrix.transpose()[0][1] == 3);

    bool rejected_ragged_matrix = false;
    try {
        (void)numerics::Matrix<int>{{1, 2}, {3}};
    } catch (const std::invalid_argument&) {
        rejected_ragged_matrix = true;
    }
    assert(rejected_ragged_matrix);

    bool rejected_fractional_integer = false;
    try {
        (void)numerics::checked_numeric_cast<short>(2.5);
    } catch (const std::invalid_argument&) {
        rejected_fractional_integer = true;
    }
    assert(rejected_fractional_integer);
    assert(numerics::checked_numeric_cast<short>(12.0) == 12);
    assert(std::abs(numerics::checked_numeric_cast<float>(1.25) - 1.25F) < 1e-6F);

    bool rejected_short_overflow = false;
    try {
        (void)numerics::checked_numeric_cast<short>(40000.0);
    } catch (const std::out_of_range&) {
        rejected_short_overflow = true;
    }
    assert(rejected_short_overflow);

    bool rejected_large_integer_boundary = false;
    try {
        const double first_value_outside_long_long =
            std::ldexp(1.0, std::numeric_limits<long long>::digits);
        (void)numerics::checked_numeric_cast<long long>(first_value_outside_long_long);
    } catch (const std::out_of_range&) {
        rejected_large_integer_boundary = true;
    }
    assert(rejected_large_integer_boundary);

    const std::vector<short> x{1, 2, 3, 4};
    const std::vector<float> y{3.0F, 5.0F, 7.0F, 9.0F};
    linreg::TypedLinearRegression<short, float> linear_model;
    const linreg::FitResult linear_fit = linear_model.fit_closed_form(x, y);
    assert(std::abs(linear_fit.intercept - 1.0) < 1e-10);
    assert(std::abs(linear_fit.slope - 2.0) < 1e-10);
    assert(std::abs(linear_model.predict(5) - 11.0) < 1e-10);

    const numerics::Matrix<int> features{{1}, {2}, {3}, {4}};
    lasso::TypedLassoRegression<int, float> lasso_model;
    bool rejected_unfitted_prediction = false;
    try {
        (void)lasso_model.predict(features);
    } catch (const std::logic_error&) {
        rejected_unfitted_prediction = true;
    }
    assert(rejected_unfitted_prediction);

    (void)lasso_model.fit(features, y, 0.0, 10000, 1e-12);
    const numerics::Matrix<int> next_row{{5}};
    const std::vector<double> lasso_prediction = lasso_model.predict(next_row);
    assert(lasso_prediction.size() == 1);
    assert(std::abs(lasso_prediction[0] - 11.0) < 1e-8);

    const numerics::CsvDataProcessor<short> csv_reader;
    const numerics::NumericDataset<short> csv_data =
        csv_reader.load("data/input/sample.csv");
    assert(csv_data.features.rows() == 8);
    assert(csv_data.features.columns() == 3);
    assert(csv_data.target.size() == 8);
    assert(csv_data.target.front() == 52);

    std::cout << "Numeric template tests passed.\n";
    return 0;
}
