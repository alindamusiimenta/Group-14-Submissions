#pragma once

#include <string>
#include <vector>

namespace lasso {

using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;

struct Dataset {
    Matrix features;
    Vector target;
};

struct BaselineResult {
    double intercept;
    double slope;
    double mse;
};

// A beginner-friendly class that stores a simple fitted line.
class LassoModel {
public:
    void fit_baseline(const Vector& x, const Vector& y);
    double predict(double x) const;
    double intercept() const;
    double slope() const;

private:
    double intercept_ = 0.0;
    double slope_ = 0.0;
    bool fitted_ = false;
};

double dot(const Vector& left, const Vector& right);
Vector matrix_vector_product(const Matrix& matrix, const Vector& vector);
double soft_threshold(double value, double threshold);
double lasso_cost(const Matrix& features, const Vector& target,
                  const Vector& coefficients, double lambda);
BaselineResult linear_regression_baseline(const Vector& x, const Vector& y);
Dataset load_csv(const std::string& path, bool has_header = true);

} // namespace lasso
