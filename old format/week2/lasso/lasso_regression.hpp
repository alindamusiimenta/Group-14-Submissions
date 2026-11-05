#pragma once

#include <cmath>

namespace lasso {

inline double soft_threshold(double value, double lambda) {
    if (lambda < 0.0) {
        lambda = -lambda;
    }

    if (value > lambda) {
        return value - lambda;
    }
    if (value < -lambda) {
        return value + lambda;
    }
    return 0.0;
}

} // namespace lasso
