#include "lasso/week3.hpp"
#include <algorithm>
#include <numeric>
#include <random>
#include <stdexcept>

namespace lasso
{

    TrainTestSplit split_dataset(const Dataset &data, double train_fraction, unsigned seed)
    {
        if (data.features.empty() || data.features.size() != data.target.size())
            throw std::invalid_argument("dataset rows and targets must match");
        if (train_fraction <= 0.0 || train_fraction >= 1.0)
            throw std::invalid_argument("train fraction must be between zero and one");
        std::vector<std::size_t> order(data.features.size());
        std::iota(order.begin(), order.end(), 0);
        std::mt19937 generator(seed);
        std::shuffle(order.begin(), order.end(), generator);
        const std::size_t train_size = static_cast<std::size_t>(data.features.size() * train_fraction);
        TrainTestSplit result;
        for (std::size_t position = 0; position < order.size(); ++position)
        {
            const std::size_t row = order[position];
            Dataset &destination = position < train_size ? result.train : result.test;
            destination.features.push_back(data.features[row]);
            destination.target.push_back(data.target[row]);
        }
        return result;
    }

} // namespace lassoa
