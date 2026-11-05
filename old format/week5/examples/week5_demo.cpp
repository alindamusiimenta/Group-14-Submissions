#include "lasso/typed_lasso_regression.hpp"
#include "linreg/typed_linear_regression.hpp"
#include "numerics/csv_data_processor.hpp"

#include <iostream>
#include <vector>

int main() {
    // The sample CSV contains whole-number values, so short is a suitable
    // storage type for this small demonstration.
    const numerics::CsvDataProcessor<short> csv_reader;
    const numerics::NumericDataset<short> data =
        csv_reader.load("data/input/sample.csv");

    std::cout << "Week 5: numeric templates\n";
    std::cout << "CSV rows: " << data.features.rows()
              << ", feature columns: " << data.features.columns() << '\n';

    // A matrix can store integers while its multiplier uses floating point.
    const numerics::Matrix<int> small_matrix{{1, 2}, {3, 4}};
    const std::vector<float> weights{0.5F, 1.5F};
    const std::vector<double> product = small_matrix.multiply(weights);
    std::cout << "Matrix product: " << product[0] << ", " << product[1] << '\n';

    // The one-feature model accepts short inputs and float targets.
    const std::vector<short> x{1, 2, 3, 4};
    const std::vector<float> y{3.0F, 5.0F, 7.0F, 9.0F};
    linreg::TypedLinearRegression<short, float> linear_model;
    linear_model.fit_closed_form(x, y);
    std::cout << "Linear prediction at x=5: " << linear_model.predict(5) << '\n';

    // LASSO accepts an integer feature matrix and floating-point target.
    const numerics::Matrix<int> lasso_features{{1}, {2}, {3}, {4}};
    lasso::TypedLassoRegression<int, float> lasso_model;
    lasso_model.fit(lasso_features, y, 0.0);
    const numerics::Matrix<int> next_row{{5}};
    std::cout << "LASSO prediction at x=5: "
              << lasso_model.predict(next_row).front() << '\n';
    return 0;
}
