// Include the header file that contains our project definitions
#include "lasso/week3.hpp"

// Include libraries needed for different operations
#include <algorithm>  // Used for shuffling the rows
#include <cmath>      // Used to check numerical values
#include <numeric>    // Used to create a sequence of row numbers
#include <random>     // Used to generate random numbers
#include <stdexcept>  // Used to report errors

namespace lasso {

// This function divides the dataset into training data and testing data
// train_fraction determines how much data is used for training
// seed helps us get the same random split when we run the program again
TrainTestSplit split_dataset(const Dataset& data, double train_fraction, unsigned seed) {

    // First, check whether the dataset contains valid data
    check_preprocessing_input(data.features, data.target);

    // Make sure the training fraction is a valid number between 0 and 1
    if (!std::isfinite(train_fraction) || train_fraction <= 0.0 || train_fraction >= 1.0) {
        throw std::invalid_argument("train fraction must be between zero and one");
    }

    // Create a list that will store the row numbers of our dataset
    std::vector<std::size_t> row_order(data.features.size());

    // Fill the list with row numbers starting from 0
    // For example: 0, 1, 2, 3, 4
    std::iota(row_order.begin(), row_order.end(), 0);

    // Create a random number generator using the seed provided
    std::mt19937 generator(seed);

    // Shuffle the row numbers into a random order
    std::shuffle(row_order.begin(), row_order.end(), generator);

    // Calculate how many rows should go into the training dataset
    const std::size_t training_count = static_cast<std::size_t>(
        static_cast<double>(data.features.size()) * train_fraction);

    // Check that both training and testing datasets will have rows
    if (training_count == 0 || training_count == data.features.size()) {
        throw std::invalid_argument("the split must leave rows in both training and test data");
    }

    // Create an empty result to store the training and testing datasets
    TrainTestSplit result;

    // Go through every row in the shuffled list
    for (std::size_t position = 0; position < row_order.size(); ++position) {

        // Get the original row number from the shuffled list
        const std::size_t row = row_order[position];

        // If the position is within the training portion, select training data
        // Otherwise, select testing data
        Dataset& destination = position < training_count ? result.train : result.test;

        // Copy the selected row's features into the correct dataset
        destination.features.push_back(data.features[row]);

        // Copy its matching target value into the same dataset
        destination.target.push_back(data.target[row]);
    }

    // Return the two completed datasets
    return result;
}

} // End of the lasso namespace
