#pragma once

#include "lasso/week3.hpp"
#include "numerics/matrix.hpp"
#include "numerics/numeric_types.hpp"

#include <stdexcept>
#include <vector>

namespace lasso {

// Accepts different numeric feature and target types, then uses the stable double API.
template <typename FeatureT, typename TargetT>
class TypedLassoRegression {
    static_assert(numerics::is_numeric_v<FeatureT>, "feature type must be numeric");
    static_assert(numerics::is_numeric_v<TargetT>, "target type must be numeric");

public:
    LassoFit fit(const numerics::Matrix<FeatureT>& features,
                 const std::vector<TargetT>& target,
                 double lambda,
                 int max_passes = 1000,
                 double tolerance = 0.000001) {
        const Matrix double_features = features.to_double();
        const Vector double_target = numerics::to_double_vector(target);
        fit_ = coordinate_descent(double_features, double_target,
                                  lambda, max_passes, tolerance);
        fitted_ = true;
        return fit_;
    }

    std::vector<double> predict(const numerics::Matrix<FeatureT>& features) const {
        if (!fitted_) {
            throw std::logic_error("fit the LASSO model before making predictions");
        }
        return predict_rows(features.to_double(), fit_.coefficients, fit_.intercept);
    }

    const LassoFit& result() const {
        if (!fitted_) {
            throw std::logic_error("fit the LASSO model before reading its result");
        }
        return fit_;
    }

private:
    LassoFit fit_{};
    bool fitted_{false};
};

} // namespace lasso
