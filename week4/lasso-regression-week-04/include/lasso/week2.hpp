#pragma once

#include "lasso/lasso_regression.hpp"

namespace lasso {

struct ScaledData {
    Matrix features;
    Vector means;
    Vector standard_deviations;
};

ScaledData standardize(const Matrix& features);
void check_preprocessing_input(const Matrix& features, const Vector& target);
Vector multiply_rows(const Matrix& matrix, const Vector& values);

struct LassoFit {
    Vector coefficients;
    double intercept;
    double cost;
    int passes;
};

LassoFit coordinate_descent(const Matrix& features, const Vector& target,
                           double lambda, int max_passes = 1000,
                           double tolerance = 0.000001);

double mean_absolute_error(const Vector& actual, const Vector& predicted);

} // namespace lasso
