#pragma once

#include "lasso/lasso_regression.hpp"
#include "numerics/dataset.hpp"

#include <string>
#include <utility>
#include <vector>

namespace numerics {

// Reads the project's simple numeric CSV format and safely converts each cell.
template <typename T>
class CsvDataProcessor {
    static_assert(is_numeric_v<T>, "CsvDataProcessor<T> requires a numeric type");

public:
    NumericDataset<T> load(const std::string& path, bool has_header = true) const {
        const lasso::Dataset raw_data = lasso::load_csv(path, has_header);

        std::vector<std::vector<T>> features;
        features.reserve(raw_data.features.size());
        for (const lasso::Vector& row : raw_data.features) {
            std::vector<T> converted_row;
            converted_row.reserve(row.size());
            for (double value : row) {
                converted_row.push_back(checked_numeric_cast<T>(value));
            }
            features.push_back(std::move(converted_row));
        }

        std::vector<T> target;
        target.reserve(raw_data.target.size());
        for (double value : raw_data.target) {
            target.push_back(checked_numeric_cast<T>(value));
        }

        return {Matrix<T>(std::move(features)), std::move(target)};
    }
};

} // namespace numerics
