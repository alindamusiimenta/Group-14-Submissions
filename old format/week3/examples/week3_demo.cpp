#include "lasso/week3.hpp"
#include <iomanip>
#include <iostream>

int main() {
    const lasso::Dataset data{{{1, 60}, {2, 65}, {3, 70}, {4, 80}, {5, 90}, {6, 92}, {7, 95}, {8, 96}},
                              {52, 55, 61, 66, 70, 74, 78, 81}};
    const auto split = lasso::split_dataset(data, 0.75, 42);
    const auto scaler = lasso::fit_scaler(split.train.features);
    const auto train_features = scaler.transform(split.train.features);
    const auto test_features = scaler.transform(split.test.features);
    const double lambda = lasso::choose_lambda(train_features, split.train.target, {0.01, 0.10, 0.50});
    const auto fit = lasso::coordinate_descent(train_features, split.train.target, lambda, 500);
    const auto predictions = lasso::predict_rows(test_features, fit.coefficients);
    const auto metrics = lasso::evaluate_regression(split.test.target, predictions);
    const auto selected = lasso::selected_features(fit.coefficients);
    std::cout << std::fixed << std::setprecision(3)
              << "train rows: " << split.train.target.size() << "\n"
              << "test rows: " << split.test.target.size() << "\n"
              << "lambda: " << lambda << "\n"
              << "test MAE: " << metrics.mae << "\n"
              << "test RMSE: " << metrics.rmse << "\n"
              << "selected features: " << selected.size() << "\n";
}
