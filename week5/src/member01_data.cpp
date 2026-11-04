#include "lasso/week3.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <stdexcept>

namespace lasso {

TrainTestSplit split_dataset(const Dataset& data, double train_fraction, unsigned seed) {
    check_preprocessing_input(data.features, data.target);
    if (!std::isfinite(train_fraction) || train_fraction <= 0.0 || train_fraction >= 1.0) {
        throw std::invalid_argument("train fraction must be between zero and one");
    }

    std::vector<std::size_t> row_order(data.features.size());
    std::iota(row_order.begin(), row_order.end(), 0);

    std::mt19937 generator(seed);
    std::shuffle(row_order.begin(), row_order.end(), generator);

    const std::size_t training_count = static_cast<std::size_t>(
        static_cast<double>(data.features.size()) * train_fraction);
    if (training_count == 0 || training_count == data.features.size()) {
        throw std::invalid_argument("the split must leave rows in both training and test data");
    }

    TrainTestSplit result;
    for (std::size_t position = 0; position < row_order.size(); ++position) {
        const std::size_t row = row_order[position];
        Dataset& destination = position < training_count ? result.train : result.test;
        destination.features.push_back(data.features[row]);
        destination.target.push_back(data.target[row]);
    }
    return result;
}

} // namespace lasso
