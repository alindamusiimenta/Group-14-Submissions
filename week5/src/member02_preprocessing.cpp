#include "lasso/week3.hpp"
#include <cmath>
#include <stdexcept>
namespace lasso
{
    void check_preprocessing_input(const Matrix &features, const Vector &target)
    {
        // Need at least one row, and one target value per feature row.
        if (features.empty() || features.size() != target.size())
        {
            // Throws if the dataset is empty or row counts don't match.
            throw std::invalid_argument("features and target must have matching rows");
        }
        const std::size_t column_count = features[0].size();
        // Column count of the first row; every other row must match.
        if (column_count == 0)
        {
            // Rows with no columns mean there are no features to train on.
            throw std::invalid_argument("at least one feature is required");
        }
        for (std::size_t row_index = 0; row_index < features.size(); ++row_index)
        {
            if (features[row_index].size() != column_count)
            {
                // Rejects ragged (uneven) rows.
                throw std::invalid_argument("feature rows must have equal sizes");
            }
            for (double value : features[row_index])
            {
                if (!std::isfinite(value))
                {
                    // Rejects NaN and +/- infinity in the features.
                    throw std::invalid_argument("feature values must be finite");
                }
            }
            if (!std::isfinite(target[row_index]))
            {
                // Same finiteness check for this row's target value.
                throw std::invalid_argument("target values must be finite");
            }
        }
    }

    bool all_finite(const Matrix &features, const Vector &target)
    {
        // Non-throwing version of the check above: returns false instead of throwing.
        if (features.empty() || features.size() != target.size() || features[0].empty())
        {
            // Empty data, mismatched row counts, or no columns.
            return false;
        }
        const std::size_t column_count = features[0].size();
        // Reference column count from the first row.
        for (std::size_t row_index = 0; row_index < features.size(); ++row_index)
        {
            if (features[row_index].size() != column_count || !std::isfinite(target[row_index]))
            {
                // Ragged row or non-finite target.
                return false;
            }
            for (double value : features[row_index])
            {
                if (!std::isfinite(value))
                {
                    // NaN or infinity found in the features.
                    return false;
                }
            }
        }
        return true;
    }

}