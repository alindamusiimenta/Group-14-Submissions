#pragma once

#include "lasso/lasso_regression.hpp"

namespace lasso {

struct ScaledData {
    Matrix features;
    Vector means;
    Vector standard_deviations;
};

// Center each feature column and divide by its standard deviation.
ScaledData standardize(const Matrix& features);

// Throw std::invalid_argument if row counts, widths, or values are invalid.
void check_preprocessing_input(const Matrix& features, const Vector& target);

// Return one dot product for each matrix row.
Vector multiply_rows(const Matrix& matrix, const Vector& values);

struct LassoFit {
    Vector coefficients;
    double intercept;
    double cost;
    int passes;
};

// Fit LASSO coefficients by updating one feature at a time.
LassoFit coordinate_descent(const Matrix& features, const Vector& target,
                           double lambda, int max_passes = 1000,
                           double tolerance = 0.000001);

double mean_absolute_error(const Vector& actual, const Vector& predicted);

} // namespace lasso
