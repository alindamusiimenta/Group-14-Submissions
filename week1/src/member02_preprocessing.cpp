#include "lasso/lasso_regression.hpp"

namespace lasso {

// Member 2: true when there is at least one row and one target per row.
bool rows_match_target(const Matrix& features, const Vector& target) {
    return !features.empty() && features.size() == target.size();
}

// Member 2: true when every row has the same number of features as row 0.
bool rows_have_equal_width(const Matrix& features) {
    for (const Vector& row : features) {
        if (row.size() != features[0].size()) {
            return false;
        }
    }
    return true;
}

} // namespace lasso
