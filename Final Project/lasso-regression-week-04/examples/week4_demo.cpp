#include "lasso/week4.hpp"
#include <iomanip>
#include <iostream>

int main() {
    // Illustrative energy dataset, not proprietary company data.
    const lasso::Dataset data{
        {{12,18,220},{15,25,240},{18,30,260},{20,35,280},
         {22,42,300},{25,48,320},{27,52,340},{29,60,360},
         {31,65,380},{33,70,400},{35,78,420},{37,82,440}},
        {8.2,9.1,10.0,10.6,11.4,12.1,12.7,13.5,14.1,14.8,15.5,16.0}
    };
    const lasso::Vector candidates{0.001,0.01,0.05,0.1,0.25,0.5};
    const auto best = lasso::select_lambda_by_cross_validation(data,candidates,4,42);
    const auto scaler = lasso::fit_scaler(data.features);
    const auto scaled = scaler.transform(data.features);
    const auto fit = lasso::coordinate_descent(scaled,data.target,best.lambda,1500,1e-7);
    const auto predictions = lasso::predict_rows(scaled,fit.coefficients,fit.intercept);
    const auto metrics = lasso::evaluate_regression(data.target,predictions);
    const auto selected = lasso::selected_features(fit.coefficients);
    std::cout << "WEEK 4: LASSO VALIDATION AND MODEL IMPROVEMENT\n"
              << "---------------------------------------------\n" << std::fixed << std::setprecision(4)
              << "Chosen lambda (lowest mean CV RMSE): " << best.lambda << "\n"
              << "Mean 4-fold validation RMSE: " << best.mean_validation_rmse << "\n"
              << "Fold RMSE values:";
    for (double score : best.fold_rmse) std::cout << " " << score;
    std::cout << "\nTraining-data MAE: " << metrics.mae
              << "\nTraining-data RMSE: " << metrics.rmse
              << "\nTraining-data R-squared: " << metrics.r_squared
              << "\nNon-zero selected features: " << selected.size() << " of " << fit.coefficients.size()
              << "\n\nNote: these metrics describe a demonstration fit, not an independent test result.\n";
    std::cout << "Coefficients (standardized feature scale):";
    for (double c : fit.coefficients) std::cout << " " << c;
    std::cout << "\n";
}
