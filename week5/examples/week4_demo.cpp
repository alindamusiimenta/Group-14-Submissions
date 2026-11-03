#include "lasso/week4.hpp"

#include <iomanip>
#include <iostream>

int main() {
    // These small values are synthetic teaching data, not measured company data.
    const lasso::Dataset data{
        {{12, 18, 220}, {15, 25, 240}, {18, 30, 260}, {20, 35, 280},
         {22, 42, 300}, {25, 48, 320}, {27, 52, 340}, {29, 60, 360},
         {31, 65, 380}, {33, 70, 400}, {35, 78, 420}, {37, 82, 440}},
        {8.2, 9.1, 10.0, 10.6, 11.4, 12.1, 12.7, 13.5, 14.1, 14.8, 15.5, 16.0}
    };
    const lasso::Vector lambda_candidates{0.001, 0.01, 0.05, 0.1, 0.25, 0.5};

    // Keep the final test rows out of both scaling and lambda selection.
    const lasso::TrainTestSplit split = lasso::split_dataset(data, 0.75, 42);
    const lasso::CrossValidationResult best =
        lasso::select_lambda_by_cross_validation(split.train, lambda_candidates, 4, 42);

    const lasso::FittedScaler scaler = lasso::fit_scaler(split.train.features);
    const lasso::Matrix scaled_training = scaler.transform(split.train.features);
    const lasso::Matrix scaled_test = scaler.transform(split.test.features);
    const lasso::LassoFit fit =
        lasso::coordinate_descent(scaled_training, split.train.target, best.lambda, 1500, 1e-7);
    const lasso::Vector predictions =
        lasso::predict_rows(scaled_test, fit.coefficients, fit.intercept);
    const lasso::RegressionMetrics metrics = lasso::evaluate_regression(split.test.target, predictions);
    const std::vector<std::size_t> selected = lasso::selected_features(fit.coefficients);

    std::cout << "WEEK 4: LASSO VALIDATION AND MODEL IMPROVEMENT\n"
              << "---------------------------------------------\n" << std::fixed << std::setprecision(4)
              << "Training rows: " << split.train.target.size() << "\n"
              << "Held-out test rows: " << split.test.target.size() << "\n"
              << "Chosen lambda (lowest mean CV RMSE): " << best.lambda << "\n"
              << "Mean 4-fold validation RMSE: " << best.mean_validation_rmse << "\n"
              << "Fold RMSE values:";
    for (double score : best.fold_rmse) {
        std::cout << " " << score;
    }
    std::cout << "\nTest MAE: " << metrics.mae
              << "\nTest RMSE: " << metrics.rmse
              << "\nTest R-squared: " << metrics.r_squared
              << "\nNon-zero selected features: " << selected.size()
              << " of " << fit.coefficients.size()
              << "\n\nNote: the dataset is a small synthetic demonstration.\n"
              << "Coefficients (standardized feature scale):";
    for (double coefficient : fit.coefficients) {
        std::cout << " " << coefficient;
    }
    std::cout << "\n";
}
