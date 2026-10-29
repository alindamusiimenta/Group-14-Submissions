#include "lasso/week3.hpp"

#include <cmath>
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

        const std::size_t column_count = features[0].size();
        if (column_count == 0)
        {
            throw std::invalid_argument("at least one feature is required");
        }

        for (std::size_t row_index = 0; row_index < features.size(); ++row_index)
        {
            if (features[row_index].size() != column_count)
            {
                throw std::invalid_argument("feature rows must have equal sizes");
            }
            for (double value : features[row_index])
            {
                if (!std::isfinite(value))
                {
                    throw std::invalid_argument("feature values must be finite");
                }
            }
            if (!std::isfinite(target[row_index]))
            {
                throw std::invalid_argument("target values must be finite");
            }
        }
    }
    // reject NaN and infinity before numerical processing.
    bool all_finite(const Matrix &features, const Vector &target)
    {
        if (features.empty() || features.size() != target.size() || features[0].empty())
        {
            return false;
        }

        const std::size_t column_count = features[0].size();
        for (std::size_t row_index = 0; row_index < features.size(); ++row_index)
        {
            if (features[row_index].size() != column_count || !std::isfinite(target[row_index]))
            {
                return false;
            }
            for (double value : features[row_index])
            {
                if (!std::isfinite(value))
                {
                    return false;
                }
            }
        }
        return true;
    }

} // namespace lasso
