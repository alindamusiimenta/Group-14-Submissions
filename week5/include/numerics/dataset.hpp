#pragma once

#include "numerics/matrix.hpp"

#include <vector>

namespace numerics {

template <typename T>
struct NumericDataset {
    Matrix<T> features;
    std::vector<T> target;
};

} // namespace numerics
