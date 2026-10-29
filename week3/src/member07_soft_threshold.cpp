#include "lasso/week3.hpp"
#include <cmath>
#include <stdexcept>

namespace lasso {

std::vector<std::size_t> selected_features(const Vector& coefficients, double threshold) {
    if (threshold < 0.0 || !std::isfinite(threshold)) {
        throw std::invalid_argument("feature-selection threshold must be non-negative and finite");
    }
    std::vector<std::size_t> selected;
    for (std::size_t index = 0; index < coefficients.size(); ++index)
        if (std::abs(coefficients[index]) > threshold) selected.push_back(index);
    return selected;
}

} // namespace lasso