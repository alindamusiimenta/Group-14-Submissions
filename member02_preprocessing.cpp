#include "lasso/week2.hpp"
#include <stdexcept>

namespace lasso
{

    // checks that rows contain usable numerical feature values.
    void check_preprocessing_input(const Matrix &features, const Vector &target)
    {
        if (features.empty() || features.size() != target.size())
        {
            throw std::invalid_argument("features and target must have matching rows");
        }
        const std::size_t width = features[0].size();
        if (width == 0)
            throw std::invalid_argument("at least one feature is required");
        for (const Vector &row : features)
        {
            if (row.size() != width)
                throw std::invalid_argument("feature rows must have equal sizes");
        }
    }

}
