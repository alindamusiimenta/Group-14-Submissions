// Prevents this file from being included more than once
#pragma once

// Include the Matrix class used to store feature data
#include "numerics/matrix.hpp"

// Include the vector library for storing target values
#include <vector>

// Start the numerics namespace
namespace numerics {

// A template allows the dataset to use different numeric data types
template <typename T>
struct NumericDataset {

    // Stores the input data (features) in a matrix
    Matrix<T> features;

    // Stores the target values that the model will predict
    std::vector<T> target;
};

// End of the numerics namespace
} 
