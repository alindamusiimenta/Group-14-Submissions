// Prevents this header file from being included more than once
#pragma once

// Include the files needed for CSV reading and dataset handling
#include "lasso/lasso_regression.hpp"
#include "numerics/dataset.hpp"

// Include standard C++ libraries
#include <string>   // Used for file names and paths
#include <utility>  // Used for moving data
#include <vector>   // Used for storing collections of values

// Start the numerics namespace
namespace numerics {

// This class reads CSV data and converts it into the selected number type
template <typename T>
class CsvDataProcessor {

    // Make sure the selected type is a numeric type
    static_assert(is_numeric_v<T>,
                  "CsvDataProcessor<T> requires a numeric type");

public:

    // This function loads data from a CSV file
    // path is the location of the CSV file
    // has_header tells the program whether the file has column headings
    NumericDataset<T> load(const std::string& path, bool has_header = true) const {

        // Read the CSV file and store its data in the original format
        const lasso::Dataset raw_data = lasso::load_csv(path, has_header);

        // Create a vector to store the converted feature values
        std::vector<std::vector<T>> features;

        // Reserve enough space for all feature rows
        features.reserve(raw_data.features.size());

        // Go through each row in the original feature data
        for (const lasso::Vector& row : raw_data.features) {

            // Create a new row to store converted values
            std::vector<T> converted_row;

            // Reserve enough space for the values in this row
            converted_row.reserve(row.size());

            // Go through each value in the current row
            for (double value : row) {

                // Safely convert the value into the selected numeric type
                converted_row.push_back(checked_numeric_cast<T>(value));
            }

            // Add the converted row to the features collection
            features.push_back(std::move(converted_row));
        }

        // Create a vector to store the target values
        std::vector<T> target;

        // Reserve enough space for all target values
        target.reserve(raw_data.target.size());

        // Go through each original target value
        for (double value : raw_data.target) {

            // Safely convert each target value into the selected numeric type
            target.push_back(checked_numeric_cast<T>(value));
        }

        // Return the converted features and target as a numeric dataset
        return {Matrix<T>(std::move(features)), std::move(target)};
    }
};

// End of the numerics namespace
} 
